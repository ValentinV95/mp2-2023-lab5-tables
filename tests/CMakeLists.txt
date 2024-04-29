set(target tests)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
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
"Test_main.cpp"
"Tests.cpp"
"../sln\\Tables\\x64\\Debug\\tests.exe"
"../src/AVLTreeTable.cpp"
"../src/HashTable.cpp"
"../src/poly.cpp" 
"../src/Test_main.cpp" 
"../src/Tests.cpp"
"../src/UnorderedTable.cpp" 
"../src/Sample.cpp"
)
file (GLOB tst
"Test_main.cpp"
"Tests.cpp"
)
add_executable(${target} ${srcs} ${hdrs})
#add_executable(${tst})
target_link_libraries(${target} gtest)
