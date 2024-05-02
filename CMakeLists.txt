cmake_minimum_required(VERSION 2.8)

project(tables)
include_directories(include gtest)

# BUILD
add_subdirectory(Sample)
add_subdirectory(test)
add_subdirectory(Gtest)
add_subdirectory(Arithmetic)
add_subdirectory(Polynomials)