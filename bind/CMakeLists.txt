project(bind_test)

cmake_minimum_required(VERSION 2.8)

include_directories(${bind_test_SOURCE_DIR})

add_executable(bind_test
                gtest/gtest_main.cc
                gtest/gtest-all.cc
                gtest/gtest.h
                unit_test.cpp
                )

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pedantic -fmax-errors=2")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(bind_test pthread)
