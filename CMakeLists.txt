cmake_minimum_required (VERSION 3.5)

set(PROJECT TrianglesIntersection)

project (${PROJECT})

set (SOURCE_ROOT src)

aux_source_directory( ${SOURCE_ROOT} SOURCES )
file(GLOB HEADERS "${SOURCE_ROOT}/*.h")

include_directories(src)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})