cmake_minimum_required(VERSION 4.3)
project(fecpp)
set(lib_name ${PROJECT_NAME})
#######################################
set(${lib_name}_libsrcs
  cpuid.cpp
  fecpp.cpp
  fecpp.h
  #fecpp_python.cpp # TODO
  )
# Conditionally add SIMD optimized sources
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64|x64)$")
  # Check for SSE2 support
  if(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
    include(CheckCXXSourceCompiles)
    set(CMAKE_REQUIRED_FLAGS "-msse2")
    check_cxx_source_compiles("
      #include <emmintrin.h>
      int main() {
        __m128i a = _mm_set1_epi32(1);
        return 0;
      }
    " HAVE_SSE2)
    if(HAVE_SSE2)
      list(APPEND ${lib_name}_libsrcs fecpp_sse2.cpp)
      set(SSE2_COMPILE_OPTIONS $<$<COMPILE_LANGUAGE:CXX>:-msse2>)
    endif()
    # Check for SSSE3 support
    set(CMAKE_REQUIRED_FLAGS "-mssse3")
    check_cxx_source_compiles("
      #include <tmmintrin.h>
      int main() {
        __m128i a = _mm_set1_epi32(1);
        a = _mm_shuffle_epi8(a, a);
        return 0;
      }
    " HAVE_SSSE3)
    if(HAVE_SSSE3)
      list(APPEND ${lib_name}_libsrcs fecpp_ssse3.cpp)
      set(SSSE3_COMPILE_OPTIONS $<$<COMPILE_LANGUAGE:CXX>:-mssse3>)
    endif()
    unset(CMAKE_REQUIRED_FLAGS)
  elseif(MSVC)
    # MSVC automatically enables SSE2 on x64, check for SSSE3 availability
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles("
      #include <tmmintrin.h>
      int main() {
        __m128i a = _mm_set1_epi32(1);
        a = _mm_shuffle_epi8(a, a);
        return 0;
      }
    " HAVE_SSSE3)
    # Always add SSE2 for MSVC x64 (it's always available)
    list(APPEND ${lib_name}_libsrcs fecpp_sse2.cpp)
    if(HAVE_SSSE3)
      list(APPEND ${lib_name}_libsrcs fecpp_ssse3.cpp)
      set(SSSE3_COMPILE_DEFINITIONS __SSSE3__)
    endif()
  endif()
endif()
source_group("" FILES ${${lib_name}_libsrcs})
#######################################
add_library(${lib_name} STATIC ${${lib_name}_libsrcs})
target_include_directories(${lib_name} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  )
# Apply SIMD compile options if available
if(DEFINED SSE2_COMPILE_OPTIONS)
  target_compile_options(${lib_name} PRIVATE ${SSE2_COMPILE_OPTIONS})
endif()
if(DEFINED SSSE3_COMPILE_OPTIONS)
  target_compile_options(${lib_name} PRIVATE ${SSSE3_COMPILE_OPTIONS})
endif()
if(DEFINED SSSE3_COMPILE_DEFINITIONS)
  target_compile_definitions(${lib_name} PRIVATE ${SSSE3_COMPILE_DEFINITIONS})
endif()
add_subdirectory(test)
#######################################
set(targetsFile ${PROJECT_NAME}-targets)
if(COMMAND xpExternPackage)
  xpExternPackage(TARGETS_FILE ${targetsFile}
    LIBRARIES ${lib_name} DEFAULT_TARGETS ${lib_name}
    BASE 0.10 XPDIFF "intro" PVT_DEPS boost
    WEB "http://www.randombit.net/code/fecpp/" UPSTREAM "github.com/randombit/fecpp"
    DESC "C++ forward error correction with SIMD optimizations"
    LICENSE "[BSD-2-Clause](http://www.randombit.net/code/fecpp/ 'BSD 2-Clause Simplified License')"
    )
elseif(NOT DEFINED CMAKE_INSTALL_CMAKEDIR)
  set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
install(TARGETS ${lib_name} EXPORT ${targetsFile}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(FILES fecpp.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_CMAKEDIR} NAMESPACE ${PROJECT_NAME}::)
set(txtFiles format.txt license.txt news.txt readme.txt)
install(FILES ${txtFiles} DESTINATION ${CMAKE_INSTALL_DOCDIR})
