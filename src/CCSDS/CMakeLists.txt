# Sources:
# --------
add_library(ccsds_lib STATIC
	src/ccsdspacket.cpp)

# Tests:
# ------
add_subdirectory(tests)

# Include directories:
# --------------------
target_include_directories(ccsds_lib
	PUBLIC include
	PRIVATE src)

# Link targets:
# -------------
target_link_libraries( ccsds_lib
	PRIVATE
	   project_options
	   project_warninngs
	   util_lib)

install(TARGETS ccsds_lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION      ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    ARCHIVE DESTINATION       ${CMAKE_INSTALL_SHAREDSTATEDIR})
