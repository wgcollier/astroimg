# https://palikar.github.io/posts/cmake_structure/


cmake_minimum_required(VERSION 3.22)

project(AstroImage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Option Settings
# ---------------
option(ONLY_COVERAGE "Build only tests necessary for coverage" FALSE)
option(LIBCPP "Build with libc++" TRUE)
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
option(ENABLE_ASAN "Enable address sanitizer" FALSE)
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" FALSE)
option(ENABLE_TESTING "Enable the building of the test" TRUE)
option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" FALSE)
option(ENABLE_CPPCHECK "Enable testing with cppcheck" FALSE)
option(SIMPLE_BUILD "Build the project as minimally as possible" FALSE)
option(BUILD_DOC "Build the project's documentation" FALSE)
option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
option(DEBUG_LOGGING "Enabling debug logging" FALSE)

# Warnings and Options
# --------------------

#   -- Establish targets for managing warnings and options
add_library(project_warnings INTERFACE)
add_library(project_options INTERFACE)

#   -- Set compiler options
target_compile_features(project_options INTERFACE cxx_std_17)

if(ONLY_COVERAGE OR ENABLE_COVERAGE)
    target_compile_options(project_options INTERFACE --coverage -O0 -g)
    target_link_libraries(project_options INTERFACE --coverage)
endif()

if(ENABLE_ASAN)
    target_compile_options(project_options INTERFACE -fsanitize=address)
    target_link_libraries(project_options INTERFACE -fsanitize=address)
endif()


target_compile_options(project_warnings
    INTERFACE
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wunused
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2)

# some GCC specific warnings. These flags are added only if the used compiler is GCC.
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(project_warnings
        INTERFACE
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wlogical-op
        -Wuseless-cast
        )
    target_link_libraries(project_options INTERFACE stdc++fs)
endif()



if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_compile_options (project_options INTERFACE -fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options (project_options INTERFACE -fcolor-diagnostics)
    endif ()
endif ()

# Extra Tools
# -----------
find_program(CCACHE ccache)
if(CCACHE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()


if(ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK}
        --suppress=syntaxError
        --enable=all
        --inconclusive)
    else()
    message(SEND_ERROR "cppcheck requested but executable not found")
    endif()
endif()


if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
    else()
    message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()

if(ENABLE_TESTING)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
    	googletest
    	GIT_REPOSITORY https://github.com/google/googletest.git
    	GIT_TAG main
    )
    FetchContent_MakeAvailable(googletest) # make gtest_main target available
    message(GTEST_SOURCE="${googletest_SOURCE_DIR}")
endif()

# Configurable header file for passing configuration parameters
# -------------------------------------------------------------
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

configure_file (
    "${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/include/config.hpp.in"
    "${PROJECT_BINARY_DIR}/src/${PROJECT_NAME}/include/config.hpp")

include_directories("${PROJECT_BINARY_DIR}/src/include")



#    -- Example Config.hpp.in file contents:
#Config.hpp.in:
#pragma once

#define PROJECT_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define PROJECT_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define PROJECT_VERSION_PATCH @PROJECT_VERSION_PATCH@

#define FILE_LOGGING 0
#define CONSOLE_LOGGING 1
#define DEBUG_LOGGING 1


# Produce documentation
# ---------------------
if(BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
                SET(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
                SET(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

                configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

                add_custom_target(doc ALL
                        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                        COMMENT "Buidling Doxygen documentation"
                        VERBATIM )
    else (DOXYGEN_FOUND)
                message("No doxygen binary found on the system.")
                SET(${BUILD_DOC} OFF)
    endif ()
endif()


# Summarize build Settings
# ------------------------
message("#########################################")
message("\t \t Summary")
message("#########################################")
message("Build type:       \t ${CMAKE_BUILD_TYPE}")
message("Install prefix:   \t ${CMAKE_INSTALL_PREFIX}")
message("Testing enabled:  \t ${ENABLE_TESTING}")
message("Clang-tidy:       \t ${ENABLE_CLANG_TIDY}")
message("Cppcheck:         \t ${ENABLE_CPPCHECK}")
message("Compiler:         \t ${CMAKE_CXX_COMPILER_ID}")
message("Sanizizers:       \t ${ENABLE_ASAN}")
message("Shared libs:      \t ${BUILD_SHARED_LIBS}")
message("Build libcpp:     \t ${LIBCPP}")
message("CCache executable:\t ${CCACHE}")
message("Building doc:     \t ${BUILD_DOC}")
message("------------------------------------------")
message("Version:          \t ${PROJECT_VERSION}")
message("########################################")

# add_subdirectory(tests)
add_subdirectory(src)
