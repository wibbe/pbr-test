
include(${CMAKE_CURRENT_SOURCE_DIR}/slg/SLG.cmake)

include_directories(${SLG_INCLUDE_DIRS})

set(SOURCE
    PBRTest.cpp
    ${SLG_SOURCE}
)

add_executable(pbr-test
               #WIN32 MACOSX_BUNDLE
               ${SOURCE})

target_link_libraries(pbr-test ${SLG_LIBRARIES})
