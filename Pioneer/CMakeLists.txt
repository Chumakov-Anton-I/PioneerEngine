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

# GLM
set(GLM_ENABLE_CXX_17 ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)

# ImGui
set(IMGUI_INCLUDES
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui.h
    ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.h
    ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.h
)
set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/misc/cpp/imgui_stdlib.cpp
)
add_library(ImGui STATIC
    ${IMGUI_INCLUDES}
    ${IMGUI_SOURCES}
)
target_link_libraries(ImGui PRIVATE glfw)
target_include_directories(ImGui
    PUBLIC  ${CMAKE_SOURCE_DIR}/external/
    PUBLIC  ${CMAKE_SOURCE_DIR}/external/imgui/
)

# ================= Engine building ===================
set(PIONEER_PUBLIC_INCLUDES
    include/pioneer/Application.hpp
    include/pioneer/Support.hpp
    include/pioneer/Logger.hpp
    include/pioneer/Layer.hpp
    include/pioneer/LayerStack.hpp
    include/pioneer/Window.hpp
    include/pioneer/UI/LayerUI.hpp
    include/pioneer/Events/Event.hpp
    include/pioneer/Events/ApplicationEvent.hpp
    include/pioneer/Events/KeyEvent.hpp
    include/pioneer/Input.hpp
    include/pioneer/KeyCodes.hpp
    include/pioneer/MouseButtonCodes.hpp
)
#set(PIONEER_PRIVATE_INCLUDES    src/)
set(PIONEER_PRIVATE_SOURCES
    src/Application.cpp
    src/Logger.cpp
    src/Window.cpp
    src/Layer.cpp
    src/LayerStack.cpp
    src/UI/LayerUI.cpp
    src/Input.cpp
)
add_library(${PROJECT_NAME} SHARED
    ${PIONEER_PUBLIC_INCLUDES}
#    ${PIONEER_PRIVATE_INCLUDES}
    ${PIONEER_PRIVATE_SOURCES}
)
target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pnrpch.hpp")
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
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            PIONEER_ENABLE_ASSERTS
    )
endif()
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    glfw
    glad
    glm
    ImGui
    opengl32
)
