set(target tables_test)

file(GLOB srcs "*.cpp")
file(GLOB hdrs "../include/*.h")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest polynoms)
target_include_directories(${target} PRIVATE "../include/")