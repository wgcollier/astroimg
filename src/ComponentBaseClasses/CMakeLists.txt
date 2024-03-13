# Sources:
# --------
add_library(component_lib INTERFACE)

# Include directories:
# --------------------
target_include_directories(component_lib INTERFACE
	"${CMAKE_CURRENT_LIST_DIR}/include")

# Link targets:
# -------------
target_link_libraries( component_lib
	INTERFACE
	   project_options
	   project_warnings)
