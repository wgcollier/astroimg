# Sources:
# --------
add_library(control_lib STATIC
	src/ctrlinterface.cpp)

# Tests:
# ------
add_subdirectory(tests)

# Include directories:
# --------------------
target_include_directories(control_lib
	PUBLIC include
	PRIVATE src)

# Link targets:
# -------------
target_link_libraries( control_lib
	PRIVATE
	   project_options
	   project_warninngs
	   util_lib
	   componentbase_lib)

install(TARGETS control_lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION      ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    ARCHIVE DESTINATION       ${CMAKE_INSTALL_SHAREDSTATEDIR})

