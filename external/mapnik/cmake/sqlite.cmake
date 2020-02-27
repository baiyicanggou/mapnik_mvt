INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/sqlite")

set(mapnik_sqlite_input_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/sqlite/sqlite_datasource.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mapnik/plugins/input/sqlite/sqlite_featureset.cpp"
)

ADD_LIBRARY(mapnik_sqlite_input STATIC
            ${mapnik_sqlite_input_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(mapnik_sqlite_input PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${mapnik_sqlite_input_SOURCE_FILES})
