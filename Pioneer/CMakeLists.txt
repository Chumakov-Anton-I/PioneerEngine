cmake_minimum_required(VERSION 3.20)

project(Pioneer)

# ============== Dependencies building ================
# ...

# ================= Engine building ===================
set(PIONEER_PUBLIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pioneer/Application.hpp
    include/pioneer/Support.hpp
)
#set(PIONEER_PRIVATE_INCLUDES
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/support.h
#)
set(PIONEER_PRIVATE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp
)
add_library(${PROJECT_NAME} SHARED
    ${PIONEER_PUBLIC_INCLUDES}
    #${PIONEER_PRIVATE_INCLUDES}
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
