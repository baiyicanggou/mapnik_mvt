#include "tiler.hh"
#include "tiler_iterator.hh"

namespace flywave {
namespace nik {

tile_bounds tiler::compute_box(const tile_ext_id &coord) const {
  auto id = coord.id();

  auto tile_bound = grid()->get_tile_extent(id.z);
  auto pc = _options->per_load_tile_count * coord.width();

  auto maxx = tile_bound.max.x > (id.x + pc) ? (id.x + pc) : tile_bound.max.x;

  tile_coord ll{id.x, id.y};
  tile_coord ur{maxx, id.y + 1};

  return tile_bounds{ll, ur};
}
} // namespace nik
} // namespace flywave
