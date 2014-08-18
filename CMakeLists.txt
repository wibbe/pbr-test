cmake_minimum_required(VERSION 2.8)
project(PBRTest)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/openctm-1.0.3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/openctm-1.0.3/lib)

set(SOURCE
    src/pbr.cpp
)

add_executable(pbr-test
               #WIN32 MACOSX_BUNDLE
               ${SOURCE})

target_link_libraries(pbr-test glfw openctm ${GLFW_LIBRARIES})
