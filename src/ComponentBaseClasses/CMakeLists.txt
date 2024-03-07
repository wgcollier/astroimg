# Sources:
# --------
add_library(componentbase_lib INTERFACE)

# Include directories:
# --------------------
target_include_directories(componentbase_lib
	INTERFACE include)

# Link targets:
# -------------
target_link_libraries( componentbase_lib
	INTERFACE
	   project_options
	   project_warninngs)

install(TARGETS componentbase_lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION      ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    ARCHIVE DESTINATION       ${CMAKE_INSTALL_SHAREDSTATEDIR})

