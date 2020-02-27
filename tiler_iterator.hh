#pragma once

#include "grid_iterator.hh"
#include "tiler.hh"

namespace flywave {
namespace nik {

class tiler_iterator {
public:
  tiler_iterator(const tiler &tr) : tiler_iterator(tr, tr.max_zoom(), 0) {}

  tiler_iterator(const tiler &tr, unsigned int startZoom,
                 unsigned int endZoom = 0)
      : _iterator(tr.grid(), startZoom, endZoom), _tiler(tr) {}

  tiler_iterator(const tiler &tr, const std::vector<uint16_t> select)
      : _iterator(tr.grid(), select), _tiler(tr) {}

  tiler_iterator(const tiler &tr, grid_iterator it)
      : _iterator(it), _tiler(tr) {}

  tiler_iterator &operator++() {
    _iterator++;
    return *this;
  }

  tiler_iterator operator++(int i) {
    return tiler_iterator{_tiler, _iterator.operator++()};
  }

  virtual std::unique_ptr<nik::mapnik_tile> operator*() const {
    return _tiler.create_tile(*(_iterator.get_current()));
  }

  bool operator==(const tiler_iterator &other) const {
    return _iterator == other._iterator;
  }

  bool operator!=(const tiler_iterator &other) const {
    return !operator==(other);
  }

  bool exhausted() const { return _iterator.exhausted(); }

  void reset(unsigned int start, unsigned int end) {
    _iterator.reset(start, end);
  }
  unsigned int size() const { return _iterator.size(); }

  const nik::grid *grid() const { return _iterator.grid(); }

  const nik::tiler &tiler() const { return _tiler; }

protected:
  const class tiler &_tiler;
  grid_iterator _iterator;
};
} // namespace nik
} // namespace flywave
