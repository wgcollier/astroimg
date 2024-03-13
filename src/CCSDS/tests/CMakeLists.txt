add_executable(ccsds_tests
	../src/ccsdspacket.cpp
	packet_tests.cpp)

# Include directories:
# --------------------
target_include_directories(ccsds_tests
	PUBLIC ../${CMAKE_CURRENT_LIST_DIR}/include
	PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

# Link targets:
# -------------
target_link_libraries( ccsds_tests
	PRIVATE
	   project_options
	   project_warnings
	   gtest_main
	   ccsds_lib
           util_lib)

include(GoogleTest)
gtest_discover_tests(ccsds_tests)
