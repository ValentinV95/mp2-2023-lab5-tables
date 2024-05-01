set(target sample)

file(GLOB srcs "sample.cpp")
file(GLOB hdrs "../include/*.h")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} polynoms)
target_include_directories(${target} PRIVATE "../include/")