INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/csv")

set(mapnik_csv_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/csv/csv_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/csv/csv_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/csv/csv_index_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/csv/csv_inline_featureset.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/csv/csv_utils.cpp"
)

ADD_LIBRARY(mapnik_csv_input STATIC
            ${mapnik_csv_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_csv_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_csv_input_SOURCE_FILES})
