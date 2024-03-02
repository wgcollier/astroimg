# Sources:
# --------
add_library(util_lib STATIC
	util.hpp
	util.cpp)

# Include directories:
# --------------------
target_include_directories(util_lib
	PUBLIC include
	PRIVATE src)


# Link targets:
# -------------
target_link_libraries( util_lib
	PRIVATE
	   project_options
	   project_warninngs)

install(TARGETS util_lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION      ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    ARCHIVE DESTINATION       ${CMAKE_INSTALL_SHAREDSTATEDIR})

