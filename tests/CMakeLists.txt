include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG main
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

enable_testing()
add_executable(spacepacket_tests main.cpp packet_tests.cpp)

target_link_libraries(
	spacepacket_tests
	PRIVATE
	GTest::GTest
	gtest_main
	spacepackets
)

add_test(spacepacket_gtest spacepacket_tests)
