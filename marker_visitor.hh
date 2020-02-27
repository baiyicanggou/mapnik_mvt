#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <mapnik/debug.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/marker.hpp>
#include <mapnik/marker_cache.hpp>
#include <mapnik/svg/svg_path_adapter.hpp>
#include <mapnik/svg/svg_path_attributes.hpp>
#include <mapnik/svg/svg_renderer_agg.hpp>
#include <mapnik/version.hpp>

#pragma GCC diagnostic push
#include <boost/algorithm/string.hpp>
#ifndef MARKER_VISITOR_HPP
#define MARKER_VISITOR_HPP

#include <boost/program_options.hpp>
#include <mapnik/warning_ignore.hpp>
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#include "agg_basics.h"
#include "agg_pixfmt_rgba.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_renderer_base.h"
#include "agg_rendering_buffer.h"
#include "agg_scanline_u.h"
#include <mapnik/warning_ignore_agg.hpp>
#pragma GCC diagnostic pop

namespace flywave {
namespace nik {

struct main_marker_visitor {

  main_marker_visitor(std::string const &svg_name, bool verbose)
      : svg_name_(svg_name), verbose_(verbose) {}

  void operator()(mapnik::marker_svg const &marker) const {
    using pixfmt = agg::pixfmt_rgba32_pre;
    using renderer_base = agg::renderer_base<pixfmt>;
    using renderer_solid = agg::renderer_scanline_aa_solid<renderer_base>;
    agg::rasterizer_scanline_aa<> ras_ptr;
    agg::scanline_u8 sl;

    double opacity = 1;
    int w = marker.width();
    int h = marker.height();
    if (w == 0 || h == 0) {
      std::tie(w, h) = marker.dimensions();
    }

    mapnik::image_rgba8 im(w + 0, h + 0);
    agg::rendering_buffer buf(im.bytes(), im.width(), im.height(),
                              im.row_size());
    pixfmt pixf(buf);
    renderer_base renb(pixf);

    mapnik::box2d<double> const &bbox = marker.get_data()->bounding_box();
    mapnik::coord<double, 2> c = bbox.center();

    agg::trans_affine mtx = agg::trans_affine_translation(-c.x, -c.y);

    mtx.translate(0.5 * im.width(), 0.5 * im.height());

    mapnik::svg::vertex_stl_adapter<mapnik::svg::svg_path_storage> stl_storage(
        marker.get_data()->source());
    mapnik::svg::svg_path_adapter svg_path(stl_storage);
    mapnik::svg::svg_renderer_agg<
        mapnik::svg::svg_path_adapter,
        agg::pod_bvector<mapnik::svg::path_attributes>, renderer_solid,
        agg::pixfmt_rgba32_pre>
        svg_renderer_this(svg_path, marker.get_data()->attributes());

    svg_renderer_this.render(ras_ptr, sl, renb, mtx, opacity, bbox);

    std::string png_name(svg_name_);
    boost::algorithm::ireplace_last(png_name, ".svg", ".png");
    demultiply_alpha(im);
    mapnik::save_to_file<mapnik::image_rgba8>(im, png_name, "png");
  }

  template <typename T> future<> operator()(T const &) const {
    return make_exception_future<>(runtime_exception("svg2png error"));
  }

private:
  std::string svg_name_;
  bool verbose_;
};
} // namespace nik
} // namespace flywave

#endif // MARKER_VISITOR_HPP
