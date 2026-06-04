cmake_minimum_required(VERSION 3.20)

project(PioneerEngine)

include(cmake/preset.cmake)

option(PIONEER_BUILD_EDITOR "Build the editor" ON)

add_subdirectory(Pioneer)
if (${PIONEER_BUILD_EDITOR})
    add_subdirectory(Editor)
endif ()
