#include "mapnik_tile.hh"
#include "grid.hh"

namespace flywave {
namespace nik {

mapnik_ext_tile::~mapnik_ext_tile() {}

mapnik::box2d<double> mapnik_ext_tile::get_bbox() {
  const grid *g = grid_;
  return g->get_bbox(id);
}

} // namespace nik
} // namespace flywave
