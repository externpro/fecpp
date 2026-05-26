cmake_minimum_required(VERSION 4.3)
project(fecpp)
set(lib_name ${PROJECT_NAME})
#######################################
set(${lib_name}_libsrcs
  fecpp.cpp
  fecpp.h
  #fecpp_python.cpp # TODO
  )
source_group("" FILES ${${lib_name}_libsrcs})
#######################################
add_library(${lib_name} STATIC ${${lib_name}_libsrcs})
target_include_directories(${lib_name} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  )
add_subdirectory(test)
#######################################
set(targetsFile ${PROJECT_NAME}-targets)
if(COMMAND xpExternPackage)
  xpExternPackage(TARGETS_FILE ${targetsFile}
    LIBRARIES ${lib_name} DEFAULT_TARGETS ${lib_name}
    BASE v0.9 XPDIFF "intro" PVT_DEPS boost
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
