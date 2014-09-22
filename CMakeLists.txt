cmake_minimum_required(VERSION 2.8)
project(PBRTest)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

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


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/openctm-1.0.3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw-3.0.4/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glew-1.11.0/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bx)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm-0.9.5.4)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/openctm-1.0.3/lib)

set(SOURCE
    src/PBRTest.cpp
    src/Framework.cpp
    src/Mesh.cpp
    src/Material.cpp
    3rdparty/glew-1.11.0/src/glew.c
)

add_executable(pbr-test
               #WIN32 MACOSX_BUNDLE
               ${SOURCE})

target_link_libraries(pbr-test glfw openctm ${GLFW_LIBRARIES})
