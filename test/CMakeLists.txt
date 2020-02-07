include_directories(${PROJECT_SOURCE_DIR})
set(externpro_DIR ${CMAKE_INSTALL_PREFIX})
set(XP_MODULE_PATH ${externpro_DIR}/share/cmake)
include(${XP_MODULE_PATH}/xpfunmac.cmake)
xpFindPkg(PKGS boost)
set(${PROJECT_NAME}_exes
  benchmark
  gen_test_vec
  #test_fec # TODO: fix compile errors
  test_recovery
  zfec
  )
set(test_recovery_deps Boost::boost)
foreach(exe ${${PROJECT_NAME}_exes})
  source_group("" FILES ${exe}.cpp)
  add_executable(${exe} ${exe}.cpp)
  target_link_libraries(${exe} PRIVATE ${lib_name} ${${exe}_deps})
endforeach()
