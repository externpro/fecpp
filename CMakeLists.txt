cmake_minimum_required(VERSION 3.31)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES .devcontainer/cmake/xproinc.cmake)
project(fecpp)
include(GNUInstallDirs)
include(xpflags)
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
set(lib ${lib_name})
if(DEFINED XP_NAMESPACE)
  set(nameSpace NAMESPACE ${XP_NAMESPACE}::)
  string(PREPEND lib "${XP_NAMESPACE}::")
endif()
if(NOT DEFINED XP_INSTALL_CMAKEDIR)
  set(XP_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
set(targetsFile ${PROJECT_NAME}-targets)
xpPackageDevel(TARGETS_FILE ${targetsFile} LIBRARIES ${lib})
install(TARGETS ${lib_name} EXPORT ${targetsFile}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(FILES fecpp.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(EXPORT ${targetsFile} DESTINATION ${XP_INSTALL_CMAKEDIR} ${nameSpace})
set(txtFiles format.txt license.txt news.txt readme.txt)
install(FILES ${txtFiles} DESTINATION ${CMAKE_INSTALL_DOCDIR})
