cmake_minimum_required(VERSION 3.16)
project(iz1_1)

include(ExternalProject)
find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


##
### Test definitions ###
##

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    add_custom_target(${PROJECT_NAME}_coverage ctest coverage)

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

if(ENABLE_CPPCHECK)

    list(APPEND CPPCHECK_CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
    )

    ExternalProject_Add(
        cppcheck
        GIT_REPOSITORY      https://github.com/danmar/cppcheck.git
        GIT_TAG             1.79
        GIT_SHALLOW         1
        CMAKE_ARGS          ${CPPCHECK_CMAKE_ARGS}
        PREFIX              ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cppcheck/download
        SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/src
        BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/build
    )

    list(APPEND CPPCHECK_ARGS
        --enable=warning,style,performance,portability,unusedFunction
        --std=c11
        --std=c++11
        --verbose
        --error-exitcode=1
        --language=c
        -DMAIN=main
        -I ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/test/*.cpp
    )

    add_custom_target(
        check
        COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS}
        COMMENT "running cppcheck"
    )

endif()


# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------

set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

##
### Source definitions ###
##

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(iz1_1 ${sources})
