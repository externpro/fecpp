include_directories(${PROJECT_SOURCE_DIR})
set(externpro_DIR ${CMAKE_INSTALL_PREFIX})
set(XP_MODULE_PATH ${externpro_DIR}/share/cmake)
include(${XP_MODULE_PATH}/xpfunmac.cmake)
if(COMMAND xpGetExtern)
  xpGetExtern(externIncs externLibs PRIVATE boost)
  # header-only boost dependency
  # so, no need for externLibs on target_link_libraries call below
endif()
set(${PROJECT_NAME}_exes
  benchmark
  gen_test_vec
  #test_fec # TODO: fix compile errors
  test_recovery
  zfec
  )
foreach(exe ${${PROJECT_NAME}_exes})
  source_group("" FILES ${exe}.cpp)
  add_executable(${exe} ${exe}.cpp)
  add_dependencies(${exe} ${lib_name})
  target_link_libraries(${exe} ${lib_name})
  target_include_directories(${exe} ${externIncs})
endforeach()
