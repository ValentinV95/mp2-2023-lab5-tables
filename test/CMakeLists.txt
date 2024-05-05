set(target tables_test)

file(GLOB srcs "*.cpp")
file(GLOB hdrs "../include/*.h" "../Gtest/*.h")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest arithmetic polynoms)
target_include_directories(${target} PRIVATE "../include/"  "../Gtest/*.h")
