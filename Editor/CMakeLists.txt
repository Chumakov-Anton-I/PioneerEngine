cmake_minimum_required(VERSION 3.20)

project(Editor)

add_executable(${PROJECT_NAME}
    src/main.cpp
)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
target_link_libraries(${PROJECT_NAME} PRIVATE Pioneer)
