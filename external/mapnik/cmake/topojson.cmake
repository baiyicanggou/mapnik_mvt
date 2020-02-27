INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/topojson")

set(mapnik_topojson_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/topojson/topojson_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/topojson/topojson_featureset.cpp"
)

ADD_LIBRARY(mapnik_topojson_input STATIC
            ${mapnik_topojson_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_topojson_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_topojson_input_SOURCE_FILES})
