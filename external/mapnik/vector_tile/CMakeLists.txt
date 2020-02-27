add_definitions(
  "-DMAPNIK_VECTOR_TILE_LIBRARY=1"
  "-DCLIPPER_INTPOINT_IMPL=mapnik::geometry::point<cInt>"
  "-DCLIPPER_PATH_IMPL=mapnik::geometry::line_string<cInt>"
  "-DCLIPPER_PATHS_IMPL=mapnik::geometry::multi_line_string<cInt>"
  "-DCLIPPER_IMPL_INCLUDE=<mapnik/geometry.hpp>"
)

 IF(APPLE)
 SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
ENDIF()	

INCLUDE_DIRECTORIES(
  "${CMAKE_CURRENT_SOURCE_DIR}/../../libxml/src/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../libjpeg/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../libpng/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../zlib"
  "${CMAKE_CURRENT_BINARY_DIR}/../../zlib"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../freetype2/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../freetype2/src/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../icu/source/common/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../icu/source/i18n/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../harfbuzz/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../libboost/boost_1_67_0"

  "${CMAKE_CURRENT_SOURCE_DIR}/../src"
  "${CMAKE_CURRENT_SOURCE_DIR}/../include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../deps"
  "${CMAKE_CURRENT_SOURCE_DIR}/../deps/agg/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../deps/mapbox/variant/include"

  "${CMAKE_CURRENT_SOURCE_DIR}/clipper/cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/proto/"
  "${CMAKE_CURRENT_BINARY_DIR}/proto/"
  "${CMAKE_CURRENT_SOURCE_DIR}/geometry/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/protozero/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

#find_package(Protobuf REQUIRED)

#ADD_CUSTOM_COMMAND(OUTPUT vector_tile.pb.cc vector_tile.pb.h
#                   COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
#		   ARGS --cpp_out ${CMAKE_CURRENT_BINARY_DIR}/proto -I ${CMAKE_CURRENT_SOURCE_DIR}/proto ${CMAKE_CURRENT_SOURCE_DIR}/proto/vector_tile.proto)

set(mapnik_vector_tile_SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_compression.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_datasource_pbf.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_featureset_pbf.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_geometry_decoder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_geometry_encoder_pbf.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_layer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_processor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_raster_clipper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector_tile_tile.cpp
)

add_definitions(-DMAPNIK_VECTOR_TILE_LIBRARY)

add_library(mapnik_vector_tile STATIC ${mapnik_vector_tile_SOURCE_FILES})

TARGET_INCLUDE_DIRECTORIES(mapnik_vector_tile PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_vector_tile_SOURCE_FILES})

SET_TARGET_PROPERTIES(mapnik_vector_tile
		                  PROPERTIES PUBLIC_HEADER "${headers}")

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(mapnik_vector_tile PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
