set(target tables_test)

#file(GLOB hdrs "../include/arithmetic.h" "../include/HashTable.h" "../include/List.h" "../include/OrderedTable.h" "../include/OrderedTable.h" "../include/stack.h" "../include/UnorderedTable.h" "../gtest/gtest.h")
file(GLOB srcs "test_hash_table.cpp" "test_main.cpp" "test_ordered_table.cpp" "test_unordered_table.cpp" "../src/Polynom.cpp" "*.cpp" "../src/HashTable.cpp" "*.cpp" "../src/arithmetic.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
