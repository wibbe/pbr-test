
cmake_minimum_required(VERSION 2.8)
project(SimpleLightweightGraphics)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
message(${PROJECT_BINARY_DIR})

# Check for and enable C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/glfw-3.0.4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/openctm-1.0.3)

set(SLG_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/glfw-3.0.4/include
    ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/glew-1.11.0/include
    #${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/stb
    ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/soil
    ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/glm-0.9.5.4
    ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/openctm-1.0.3/lib)

set(SLG_LIBRARIES openctm glfw ${GLFW_LIBRARIES})

SET(SLG_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Texture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/FrameBuffer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Buffer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Input.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/File.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Mesh.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/MeshHelpers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/CameraControllers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/Log.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/glew-1.11.0/src/glew.c
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/soil/SOIL.c
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/soil/image_DXT.c
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/soil/stb_image_aug.c
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/soil/image_helper.c
  ${CMAKE_CURRENT_SOURCE_DIR}/slg/3rdparty/soil/stbi_DDS_aug_c.h
)
