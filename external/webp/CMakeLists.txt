set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

project(webp C)

IF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-constant-conversion -Wno-array-bounds -Wno-unused-function -Wno-enum-compare -Wno-implicit-function-declaration -Wno-int-conversion -Wno-format-extra-args -Wno-float-conversion -Wno-tautological-pointer-compare -Wno-attributes -Wno-unknown-pragmas -Wno-tautological-compare -Wno-attributes -Wno-unused-const-variable -Wno-sign-compare -Wno-deprecated-declarations")

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-but-set-variable -Wno-misleading-indentation")
ENDIF()
ENDIF()

set(VERSION 1.9.9)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

ADD_DEFINITIONS(-DNDEBUG)

FILE(GLOB WEBP_DEC_SRCS
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src/dec/*c
)

FILE(GLOB WEBP_DSP_SRCS
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/*c
)

FILE(GLOB WEBP_ENC_SRCS
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src/enc/*c
)

FILE(GLOB WEBP_UTILS_SRCS
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*c
)

FILE(GLOB WEBP_HEADER_FILES
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include/webp/*h
)

add_library(webp STATIC ${WEBP_DEC_SRCS} ${WEBP_DSP_SRCS} ${WEBP_ENC_SRCS} ${WEBP_UTILS_SRCS})
target_link_libraries(webp m)

SOURCE_GROUP("src" FILES ${WEBP_DEC_SRCS} ${WEBP_DSP_SRCS} ${WEBP_ENC_SRCS} ${WEBP_UTILS_SRCS})
SOURCE_GROUP("include" FILES ${WEBP_HEADER_FILES})

SET_TARGET_PROPERTIES(webp
    PROPERTIES PUBLIC_HEADER "${headers}")

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
	SET_TARGET_PROPERTIES(webp PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
