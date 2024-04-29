
file(GLOB hdrs "../include/arithmetic.h" 
	"../include/AVLTreeTable.h"
	"../include/HashTable.h"
	"../include/poly.h "
	"../include/Unordered" 
	"../include/Table.h "
	"../include/gtest.h"
	"../include/list.h"
	"../include/stack.h")
file(GLOB srcs 
"Sample.cpp"
"Sample.exe"
"../src/AVLTreeTable.cpp"
"../src/HashTable.cpp"
"../src/poly.cpp" 
"../src/UnorderedTable.cpp" 
"../src/Sample.cpp"
)

add_executable(tables ${srcs} ${hdrs})
