set(target main_tests)

file(GLOB_RECURSE tests "*.cpp")

add_executable(${target} ${tests})
target_link_libraries(${target} PUBLIC gtest main_libs)
