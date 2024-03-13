add_executable(control_tests
	../src/ctrlinterface.cpp
	ctrl_tests.cpp)

# Include directories:
# --------------------
target_include_directories(control_tests
	PUBLIC ../include
	PRIVATE ../src)
# set(component_include
#     "$<TARGET_PROPERTY:componentbase_lib,INTERFACE_INCLUDE_DIRECTORIES>")
# target_include_directories(control_tests PRIVATE "${component_include}")
#target_include_directories(control_tests )

# Link targets:
# -------------
target_link_libraries( control_tests
	PRIVATE
	   project_options
	   project_warnings
	   gtest_main
	   control_lib)

include(GoogleTest)
gtest_discover_tests(control_tests)
