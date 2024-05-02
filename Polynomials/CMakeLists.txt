set(target polynoms)

file(GLOB hdrs "../include/polynomials.h")

add_library(${target} STATIC polynomials.cpp ${hdrs})
target_include_directories(${target} PRIVATE "../include/")