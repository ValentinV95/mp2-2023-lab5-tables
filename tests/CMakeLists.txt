set(target tables_tests)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
file(GLOB hdrs "../include/arithmetic.h" 
	"../include/AVLTreeTable.h"
	"../include/HashTable.h"
	"../include/poly.h "
	"../include/Unordered" 
	"../include/Table.h "
	"../include/gtest.h"
	"../include/list.h"
	"../gtest/gtest.h"
	"../include/stack.h"
)
file(GLOB srcs 
"Test_main.cpp"
"Tests.cpp"
"../src/AVLTreeTable.cpp"
"../src/HashTable.cpp"
"../src/poly.cpp" 
"../src/UnorderedTable.cpp" 
"../src/arithmetic.cpp"
)
add_executable(${target} ${srcs} ${hdrs})

target_link_libraries(${target} gtest)
