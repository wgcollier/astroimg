# Sources:
# --------
add_library(ccsds_lib STATIC
	src/ccsdspacket.cpp)

# Include directories:
# --------------------
target_include_directories(ccsds_lib
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
	PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
message(CURRENT_LIST_DIR="${CMAKE_CURRENT_LIST_DIR}")
message(Ccsds_Include="${CMAKE_CURRENT_LIST_DIR}/include")

# Link targets:
# -------------
target_link_libraries( ccsds_lib
	PRIVATE
	   project_options
	   project_warnings
	   util_lib)

# install(TARGETS ccsds_lib
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
