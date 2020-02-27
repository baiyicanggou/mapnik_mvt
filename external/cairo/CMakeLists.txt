project(cairo)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

IF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-parentheses-equality -Wno-unused-local-typedef -Wno-uninitialized -Wno-incompatible-pointer-types -Wno-unused-variable -Wno-float-conversion -Wno-implicit-function-declaration -Wno-deprecated-declarations -Wno-shadow -Wno-unused-function -Wno-format-extra-args -Wno-unknown-pragmas -Wno-tautological-compare -Wno-attributes -Wno-unused-const-variable -Wno-sign-compare -Wno-deprecated-declarations")
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-cpp -Wno-unused-but-set-variable -Wno-misleading-indentation -Wno-strict-aliasing")
    ENDIF()
ENDIF()

IF (WIN32)
  INCLUDE_DIRECTORIES(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/win32
                             ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/win32/include")
ENDIF()

IF(APPLE)
  INCLUDE_DIRECTORIES(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/mac
                             ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/mac/include")
ENDIF()

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
INCLUDE_DIRECTORIES( AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/linux
                            ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/linux/include")
ENDIF()


add_definitions(-DCAIRO_NO_MUTEX=1)
add_definitions(-DHAVE_UINT64_T=1)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/src
    "${CMAKE_CURRENT_SOURCE_DIR}/../fontconfig/src/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../fontconfig/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libexpat/expat/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/src/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../zlib"
    "${CMAKE_CURRENT_BINARY_DIR}/../zlib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libpng/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../pixman/pixman/"
    "${CMAKE_CURRENT_BINARY_DIR}/../pixman/pixman/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/src/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/common/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/i18n/"
)

SET(PNG_FOUND TRUE)
SET(FREETYPE_FOUND TRUE)
SET(FONTCONFIG_FOUND TRUE)
SET(LIBXML2_FOUND TRUE)
SET(ZLIB_FOUND TRUE)

include(Configure_config.cmake)
include(Configure_features.cmake)

if (WIN32)
    set(CAIRO_LIBS gdi32 msimg32 user32 winmm)
endif()

SET(CAIRO_HAS_PTHREAD FALSE)

add_subdirectory(src)
