set(target polynoms)

file(GLOB hdrs "../include/*.h")

add_library(${target} STATIC polynoms.cpp postfix.cpp error.cpp ${hdrs})
target_include_directories(${target} PRIVATE "../include/")