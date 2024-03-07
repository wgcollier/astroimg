add_library(control_tests_lib STATIC
	ctrl_tests.cpp)

# Include directories:
# --------------------
target_include_directories(control_tests_lib
	PUBLIC include
	PRIVATE src)

# Link targets:
# -------------
target_link_libraries( control_tests_lib
	PRIVATE
	   project_options
	   project_warninngs)
