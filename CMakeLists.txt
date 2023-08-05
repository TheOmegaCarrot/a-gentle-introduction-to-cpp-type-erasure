cmake_minimum_required(VERSION 3.16.0)

project(
  a_gentle_introduction_to_cpp_type_erasure
  VERSION 0.0.0
  LANGUAGES CXX
  )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(compiler_flags)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Course")
