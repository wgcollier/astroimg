include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG main
)
FetchContent_MakeAvailable(googletest) # make gtest_main target available

enable_testing()
add_executable(spacepacket_tests main.cpp)

target_link_libraries(
	spacepacket_tests
	PRIVATE
	gtest
	gtest_main
	util_tests_lib
	ccsds_tests_lib
	control_tests_lib
)
