include_directories(${PROJECT_SOURCE_DIR})
set(externpro_DIR ${CMAKE_INSTALL_PREFIX})
include(usexp-externpro)
if(COMMAND xpFindPkg)
  xpFindPkg(PKGS boost) # boost added to include_directories
endif()
set(${PROJECT_NAME}_exes
  benchmark
  gen_test_vec
  test_fec
  test_recovery
  zfec
  )
foreach(exe ${${PROJECT_NAME}_exes})
  source_group("" FILES ${exe}.cpp)
  add_executable(${exe} ${exe}.cpp)
  add_dependencies(${exe} ${lib_name})
  target_link_libraries(${exe} ${lib_name})
endforeach()
