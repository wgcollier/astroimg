# Sources:
# --------
add_library(control_lib STATIC
	src/ctrlinterface.cpp)

# Tests:
# ------
#add_subdirectory(tests)

# Include directories:
# --------------------
target_include_directories(control_lib
	PUBLIC
	   ${CMAKE_CURRENT_LIST_DIR}/include
	   ${CMAKE_CURRENT_LIST_DIR}/src)

# Link targets:
# -------------
target_link_libraries( control_lib
	PRIVATE
	   project_options
	   project_warnings
	PUBLIC
	   component_lib)

# install(TARGETS control_lib
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
#     RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
#     LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
#     INCLUDES DESTINATION      ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
#     ARCHIVE DESTINATION       ${CMAKE_INSTALL_SHAREDSTATEDIR})

# Tests:
# ------
 if(ENABLE_TESTING)
     add_subdirectory(tests)
 endif()
