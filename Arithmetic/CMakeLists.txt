set(target arithmetic)

file(GLOB hdrs "../include/*.h")

add_library(${target} STATIC arithmetic.cpp ${hdrs})
target_include_directories(${target} PRIVATE "../include/")