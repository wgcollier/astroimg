add_library(ccsds_tests_lib STATIC
	packet_tests.cpp)

# Include directories:
# --------------------
target_include_directories(ccsds_tests_lib
	PUBLIC include
	PRIVATE src)

# Link targets:
# -------------
target_link_libraries( ccsds_tests_lib
	PRIVATE
	   project_options
	   project_warninngs
	   util_lib)

