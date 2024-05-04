set(target sample)

file(GLOB srcs "Sample.cpp")

add_executable(${target} ${srcs})
target_link_libraries(${target} arithmetic polynoms)
target_include_directories(${target} PRIVATE "../include/")