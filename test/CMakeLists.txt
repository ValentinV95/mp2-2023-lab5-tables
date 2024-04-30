set(target tables_test)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
file(GLOB hdrs "*.h*" "../include/*.h")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
