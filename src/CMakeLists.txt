file(GLOB_RECURSE lib_source *.cpp)
add_library(main_libs "${lib_headers}" "${lib_source}")
