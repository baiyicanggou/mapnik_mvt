INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/shape")

set(mapnik_shape_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/shape/dbfile.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/shape/shape_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/shape/shape_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/shape/shape_index_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/shape/shape_io.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/shape/shape_utils.cpp"
)

ADD_LIBRARY(mapnik_shape_input STATIC
            ${mapnik_shape_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_shape_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_shape_input_SOURCE_FILES})
