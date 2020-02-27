//
//  main.cpp
//  mapnik_test
//
//  Created by hj on 2020/2/12.
//


#include <mapnik/agg_renderer.hpp>
#include <mapnik/color.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/debug.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/map.hpp>
#include <mapnik/version.hpp>
#include <mapnik/box2d.hpp>
#include <mapnik/coord.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/image_scaling.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>
#include <mapnik/rule.hpp>

#include <datasource_impl.hh>
#include <mapnik_grid.hh>
#include <mapnik_impl.hh>
#include <mapnik_source.hh>
#include <mapnik_tiler.hh>
#include <mvt_tiler.hh>
#include <tiler_iterator.hh>
#include <utfgrid_tiler.hh>

#include <tiler_c_api.h>
#include <mapnik_c_api.h>


#if MAPNIK_VERSION < 300000
#error flywave-mapnik requires Mapnik 3
#endif

static inline void calculate_layers_sd(mapnik::Map &map) {
    const auto &styles = map.styles();
    for (auto &layer : map.layers()) {
        double min_sd = 1000000000;
        double max_sd = 0;
        for (const auto &style_name : layer.styles()) {
            const auto style_itr = styles.find(style_name);
            if (style_itr == styles.end()) {
                continue;
            }
            const auto &style = style_itr->second;
            for (const auto &rule : style.get_rules()) {
                min_sd = std::min(min_sd, rule.get_min_scale());
                max_sd = std::max(max_sd, rule.get_max_scale());
            }
        }
        if (min_sd != 1000000000) {
            layer.set_minimum_scale_denominator(min_sd);
        }
        if (max_sd != 0) {
            layer.set_maximum_scale_denominator(max_sd);
        }
    }
}
extern "C" {
void writeTileFunc(void *ctx, _mapnik_tile_t *t){}
void writeMvtTileFunc(void *ctx, _mvt_tile_t *t){}
void writeUtfgridTileFunc(void *ctx, _utfgrid_tile_t *t){}
}

int main(int argc, const char * argv[]) {
    std::string style="/Volumes/Work/flywave-mapnik/build/mapnik_test/map.xml";
    auto map =  new mapnik::Map(800, 600);
    try {
        mapnik::load_map(*map, style);
    } catch (std::exception const &ex) {
    }
    calculate_layers_sd(*map);
    std::cout<<map->layers().size()<<std::endl;
    
    mapnik_map_t *m = new mapnik_map_t;
    m->m = map;
    
    auto opts = tiler_source_options_new();
    tiler_source_options_add(opts, "test", m);
    auto source  = tiler_source_new(opts);
    
    auto grid = tiler_global_mercator_grid(256);
    
    auto options = mvt_tiler_options_new("test");
    mvt_tiler_options_add_layer(options,"layerA");
    mvt_tiler_options_add_layer(options,"layerB");
    mvt_tiler_options_add_layer(options,"layerC");
    mvt_tiler_options_add_layer(options,"layerD");

    auto tl =mvt_tiler_new(source,grid,options);
    
    mvt_tiler_render(tl,3,2,nullptr);
}
