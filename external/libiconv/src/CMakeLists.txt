cmake_minimum_required(VERSION 2.8.12)
IF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-type-limits -Wno-parentheses-equality -Wno-static-in-inline -Wno-unused-variable -Wno-parentheses-equality -Wno-static-in-inline -Wno-float-conversion -Wno-shadow -Wno-unused-function -Wno-format-extra-args -Wno-unknown-pragmas -Wno-tautological-compare -Wno-attributes -Wno-unused-const-variable -Wno-sign-compare -Wno-deprecated-declarations")
ENDIF()

file(GLOB_RECURSE SOURCE_FILES *.c *.h ../include/*.h)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PUBLIC "../include")
target_compile_definitions(${TARGET_NAME} PRIVATE LIBDIR=\".\" ICONV_CONST=const HAVE_WORKING_O_NOFOLLOW=1)

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
