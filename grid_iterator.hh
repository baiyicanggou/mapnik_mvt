#ifndef GRIDITERATOR_HPP
#define GRIDITERATOR_HPP

#include <algorithm>
#include <iterator>

#include "grid.hh"

namespace flywave {
namespace nik {

class grid_iterator : public std::iterator<std::input_iterator_tag, tile_id *> {
public:
  grid_iterator(const grid *grid, unsigned int startZoom,
                unsigned int endZoom = 0,
                const std::vector<uint16_t> &select = std::vector<uint16_t>{})
      : _grid(grid), _start_zoom(startZoom), _end_zoom(endZoom),
        _select(select) {
    if (_start_zoom < _end_zoom)
      std::swap(_start_zoom, _end_zoom);

    if (!_select.empty()) {
      std::sort(_select.begin(), _select.end());
      _end_zoom = _select.front();
      _start_zoom = _select.back();
    }
    _current_tile.z = _start_zoom;
    set_tile_bounds(_start_zoom);
  }

  grid_iterator(const grid *grid, const std::vector<uint16_t> &select)
      : grid_iterator(grid, 20, 0, select) {}

  grid_iterator &operator++() {
    if (exhausted())
      return *this;
    if (++(_current_tile.x) == _bounds.max.x) {
      if (++(_current_tile.y) == _bounds.max.y) {
        if (_current_tile.z > _end_zoom) {
          (_current_tile.z)--;
          if (!_select.empty()) {
            bool exsit = false;
            while (!exsit) {
              for (auto i : _select) {
                if (i != _current_tile.z) {
                  continue;
                }
                exsit = true;
                break;
              }
              if (!exsit)
                (_current_tile.z)--;
            }
            if (!exsit)
              return *this;
          }
          set_tile_bounds(_current_tile.z);
        }
      } else {
        _current_tile.x = _bounds.min.x;
      }
    }

    return *this;
  }

  grid_iterator operator++(int) {
    grid_iterator result(*this);
    ++(*this);
    return result;
  }

  bool operator==(const grid_iterator &other) const {
    return _current_tile == other._current_tile &&
           _start_zoom == other._start_zoom && _end_zoom == other._end_zoom &&
           _bounds == other._bounds && _grid == other._grid;
  }

  bool operator!=(const grid_iterator &other) const {
    return !operator==(other);
  }

  virtual const tile_id *get_current() const { return &_current_tile; }

  bool exhausted() const {
    return _current_tile.z == _end_zoom && (_current_tile.x == _bounds.max.x ||
                                            _current_tile.y == _bounds.max.y);
  }

  void reset(unsigned int start, unsigned int end) {
    if (start < end)
      throw std::runtime_error(
          "Starting zoom level cannot be less than the end zoom level");

    _current_tile.z = _start_zoom = start;
    _end_zoom = end;
    if (!_select.empty()) {
      _current_tile.z = _end_zoom = _select.front();
      _start_zoom = _select.back();
    }

    set_tile_bounds(start);
  }

  unsigned int size() const {
    unsigned int size = 0;
    for (unsigned int zoom = _end_zoom; zoom <= _start_zoom; ++zoom) {
      tile_bounds zoomBound = _grid->get_tile_extent(zoom);
      size += (zoomBound.width() + 1) * (zoomBound.height() + 1);
    }
    return size;
  }

  const nik::grid *grid() const { return _grid; }

protected:
  void set_tile_bounds(int zoom) {
    _bounds = _grid->get_tile_extent(zoom);
    _current_tile.x = _bounds.min.x;
    _current_tile.y = _bounds.min.y;
  }

  const nik::grid *_grid;
  unsigned int _start_zoom;
  unsigned int _end_zoom;
  tile_bounds _bounds;
  tile_id _current_tile;
  std::vector<uint16_t> _select;
};
} // namespace nik
} // namespace flywave
#endif /* GRIDITERATOR_HPP */
