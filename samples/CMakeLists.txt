file(GLOB hdrs "../include/arithmetic.h" "../include/HashTable.h" "../include/List.h" "../include/OrderedTable.h" "../include/OrderedTable.h" "../include/stack.h" "../include/UnorderedTable.h")
file(GLOB srcs "main_tables.cpp" "../src/Polynom.cpp" "*.cpp" "../src/HashTable.cpp" "*.cpp" "../src/arithmetic.cpp")

add_executable(tables ${srcs} ${hdrs})
