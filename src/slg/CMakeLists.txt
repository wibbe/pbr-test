
cmake_minimum_required(VERSION 2.8)
project(SimpleLightweightGraphics)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/EnableCpp11.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/openctm-1.0.3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glew-1.11.0/include
                    #${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb
                    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/soil
                    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm-0.9.5.4
                    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/openctm-1.0.3/lib)

SET(SOURCE
  Camera.cpp
  Shader.cpp
  Texture.cpp
  FrameBuffer.cpp
  Window.cpp
  Buffer.cpp
  Input.cpp
  File.cpp
  Mesh.cpp
  MeshHelpers.cpp
  CameraControllers.cpp
  Log.cpp

  3rdparty/glew-1.11.0/src/glew.c
  3rdparty/soil/SOIL.c
  3rdparty/soil/image_DXT.c
  3rdparty/soil/stb_image_aug.c
  3rdparty/soil/image_helper.c
  3rdparty/soil/stbi_DDS_aug_c.h
)

ADD_LIBRARY(slg ${SOURCE})
TARGET_LINK_LIBRARIES(slg openctm ${GLFW_LIBRARIES})

set(SLG_LIBRARIES slg openctm glfw ${GLFW_LIBRARIES} CACHE STRING "SLG and dependencies of SLG")
set(SLG_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm-0.9.5.4
    CACHE STRING "SLG include directories")
