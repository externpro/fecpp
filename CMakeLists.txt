cmake_minimum_required(VERSION 3.0)
project(fecpp)
include(flags)
set(lib_name ${PROJECT_NAME})
#######################################
# library sources
set(${lib_name}_libsrcs
  fecpp.cpp
  fecpp.h
  #fecpp_python.cpp # TODO
  )
source_group("" FILES ${${lib_name}_libsrcs})
#######################################
# library
add_library(${lib_name} STATIC ${${lib_name}_libsrcs})
add_subdirectory(test)
#######################################
# install
install(TARGETS ${lib_name} EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(FILES fecpp.h DESTINATION include/fecpp)
install(EXPORT ${PROJECT_NAME}-targets DESTINATION lib/cmake)
set(txtFiles format.txt license.txt news.txt readme.txt)
install(FILES ${txtFiles} DESTINATION share/fecpp)
