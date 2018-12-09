cmake_policy(SET CMP0048 NEW)
project (mimic_standard_library VERSION 0.0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 3.7)

enable_testing()
add_subdirectory(googletest)

add_library(NJM_GOOGLE_TEST "./googletest/googletest/src/gtest_main.cc")
target_include_directories(NJM_GOOGLE_TEST PUBLIC "./googletest/googletest/include")
target_link_libraries(NJM_GOOGLE_TEST gtest)

function(njm_add_unit_test)
  set(options)
  set(one_value_args TARGET)
  set(multi_value_args SOURCES LIBS)
  cmake_parse_arguments(NJM_ADD_UNIT_TEST
    "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})
  add_executable(${NJM_ADD_UNIT_TEST_TARGET} ${NJM_ADD_UNIT_TEST_SOURCES})
  target_link_libraries(${NJM_ADD_UNIT_TEST_TARGET} ${NJM_ADD_UNIT_TEST_LIBS} NJM_GOOGLE_TEST)
  add_test(${NJM_ADD_UNIT_TEST_TARGET}_TEST_TARGET ${NJM_ADD_UNIT_TEST_TARGET})
endfunction(njm_add_unit_test)

function(njm_add_library)
  set(options)
  set(one_value_args TARGET)
  set(multi_value_args SOURCES LIBS)
  cmake_parse_arguments(NJM_ADD_LIBRARY
    "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})
  list(LENGTH "${NJM_ADD_LIBRARY_SOURCES}" NUM_SOURCES)
  if(${NUM_SOURCES} GREATER 0)
    set(IS_INTERFACE "")
  else()
    set(IS_INTERFACE "INTERFACE")
  endif()
  add_library(${NJM_ADD_LIBRARY_TARGET} ${IS_INTERFACE} ${NJM_ADD_LIBRARY_SOURCES})
  target_link_libraries(${NJM_ADD_LIBRARY_TARGET} ${NJM_ADD_LIBRARY_LIBS})
  target_include_directories(${NJM_ADD_LIBRARY_TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
endfunction(njm_add_library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(src)
