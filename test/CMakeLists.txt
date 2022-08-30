set(XP_MODULE_PATH ${CMAKE_MODULE_PATH})
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
