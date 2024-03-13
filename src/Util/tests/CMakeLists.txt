add_executable(util_tests
	../src/util.cpp
	util_tests.cpp)

target_include_directories(util_tests
	PUBLIC ../include
	PRIVATE ../src)

target_link_libraries( util_tests
	PRIVATE
	   project_options
	   project_warnings
	   gtest_main)

include(GoogleTest)
gtest_discover_tests(util_tests)
