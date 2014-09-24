cmake_minimum_required(VERSION 2.8)
project(PBRTest)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/slg/cmake/EnableCpp11.cmake)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/slg)
include_directories(${SLG_INCLUDE_DIRS})

set(SOURCE
    src/PBRTest.cpp
)

add_executable(pbr-test
               #WIN32 MACOSX_BUNDLE
               ${SOURCE})

message(${SLG_LIBRARIES})

target_link_libraries(pbr-test ${SLG_LIBRARIES})
