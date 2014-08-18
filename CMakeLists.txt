cmake_minimum_required(VERSION 2.8)
project(PBRTest CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb)

set(SOURCE
    src/pbr.cpp
)

add_executable(pbr-test
               #WIN32 MACOSX_BUNDLE
               ${SOURCE})

target_link_libraries(pbr-test glfw ${GLFW_LIBRARIES})
