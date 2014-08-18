
set(CTMLIB_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/openctm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/stream.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/compressRAW.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/compressMG1.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/compressMG2.c

    ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblzma/Alloc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblzma/LzFind.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblzma/LzmaDec.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblzma/LzmaEnc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblzma/LzmaLib.c)

set(CTM_CONV
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/rply/rply.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/tinyxml/tinystr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/tinyxml/tinyxml.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/tinyxml/tinyxmlparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/tinyxml/tinyxmlerror.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/meshio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ctm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ply.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/stl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/3ds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/dae.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/obj.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/lwo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/off.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/wrl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ctmconv.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/systimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/convoptions.cpp)

add_definitions(-DOPENCTM_BUILD -DLZMA_PREFIX_CTM)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools/rply)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tools/tinyxml)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/liblzma)

add_library(openctm ${CTMLIB_SOURCE})

add_executable(ctmconv ${CTM_CONV})
target_link_libraries(ctmconv openctm)