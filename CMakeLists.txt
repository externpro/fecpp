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
# version
if(DEFINED FECPP_VER)
  set(ver _${FECPP_VER})
  set(verDir /${PROJECT_NAME}${ver})
endif()
#######################################
# library
add_library(${lib_name} STATIC ${${lib_name}_libsrcs})
set_target_properties(${lib_name} PROPERTIES OUTPUT_NAME ${lib_name}${ver})
add_subdirectory(test)
#######################################
# install
set(targetsFile ${PROJECT_NAME}${ver}-targets)
install(TARGETS ${lib_name} EXPORT ${targetsFile}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
install(FILES fecpp.h DESTINATION include${verDir}/${PROJECT_NAME})
install(EXPORT ${targetsFile} DESTINATION lib/cmake)
set(txtFiles format.txt license.txt news.txt readme.txt)
install(FILES ${txtFiles} DESTINATION share${verDir}/${PROJECT_NAME})
