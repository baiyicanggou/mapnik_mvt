#ifndef MAPNIK_DATASOURCE_IMPL_H
#define MAPNIK_DATASOURCE_IMPL_H

#include <mapnik/datasource.hpp>

#ifdef __cplusplus
extern "C" {
#endif

struct _mapnik_datasource_t {
  mapnik::datasource_ptr ptr;
};

#ifdef __cplusplus
}
#endif

#endif