add_library(util_tests_lib STATIC
	util_tests.cpp)

target_include_directories(util_tests_lib
	PUBLIC include
	PRIVATE src)

target_link_libraries( util_tests_lib
	PRIVATE
	   project_options
	   project_warnings)
