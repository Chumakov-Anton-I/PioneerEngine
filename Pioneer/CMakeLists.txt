cmake_minimum_required(VERSION 3.20)

project(Pioneer)

# ============== Dependencies building ================
# spdlog
add_subdirectory(${CMAKE_SOURCE_DIR}/external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

# glad
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)

# sigslot
add_subdirectory(${CMAKE_SOURCE_DIR}/external/sigslot ${CMAKE_CURRENT_BINARY_DIR}/sigslot)

# ================= Engine building ===================
set(PIONEER_PUBLIC_INCLUDES
    include/pioneer/Application.hpp
    include/pioneer/Support.hpp
    include/pioneer/Logger.hpp
    include/pioneer/Layer.hpp
    include/pioneer/LayerStack.hpp
)
set(PIONEER_PRIVATE_INCLUDES
    src/Window.hpp
)
set(PIONEER_PRIVATE_SOURCES
    src/Application.cpp
    src/Logger.cpp
    src/Window.cpp
    src/Layer.cpp
    src/LayerStack.cpp
)
add_library(${PROJECT_NAME} SHARED
    ${PIONEER_PUBLIC_INCLUDES}
    ${PIONEER_PRIVATE_INCLUDES}
    ${PIONEER_PRIVATE_SOURCES}
)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        C_VISIBILITY_PRESET hidden
        CXX_VISIBILITY_PRESET hidden
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        PIONEER_LIBRARY_BUILD
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE        ${CMAKE_CURRENT_SOURCE_DIR}/src #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    glfw
    glad
    Pal::Sigslot
)
