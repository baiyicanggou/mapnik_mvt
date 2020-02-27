#ifndef __FLYWAVE_BBOX_CLIPPER_HH__
#define __FLYWAVE_BBOX_CLIPPER_HH__

#include <mapnik/box2d.hpp>
#include <mapnik/geometry.hpp>

namespace flywave {
namespace nik {
namespace bbox_clipper {

template <typename T> using point = mapnik::geometry::point<T>;
template <typename T> using line_string = mapnik::geometry::line_string<T>;
template <typename T>
using multi_line_string = mapnik::geometry::multi_line_string<T>;
template <typename T> using linear_ring = mapnik::geometry::linear_ring<T>;

enum out_code : uint8_t {
  INSIDE = 0,
  RIGHT = 1,
  BOTTOM = 2,
  LEFT = 4,
  TOP = 8
};

enum clip_code : uint8_t { OUTBOX = 0, INBOX = 1, FIRST_CLIPPED = 2 };

const uint8_t TWOBITS = 16;

template <typename T>
inline int8_t compute_outcode(const point<T> &point,
                              const mapnik::box2d<T> &bbox) {
  int8_t result = INSIDE;
  if (point.y > bbox.maxy()) {
    result = BOTTOM;
  } else if (point.y < bbox.miny()) {
    result = TOP;
  }
  if (point.x > bbox.maxx()) {
    result |= RIGHT;
  } else if (point.x < bbox.minx()) {
    result |= LEFT;
  }
  return result;
}

template <typename T>
inline int8_t compute_maillot_outcode(const point<T> &point,
                                      const mapnik::box2d<T> &bbox) {
  if (point.x < bbox.minx()) {
    if (point.y > bbox.maxy())
      return LEFT | BOTTOM | TWOBITS;
    if (point.y < bbox.miny())
      return LEFT | TOP | TWOBITS;
    return LEFT;
  }
  if (point.x > bbox.maxx()) {
    if (point.y > bbox.maxy())
      return RIGHT | BOTTOM | TWOBITS;
    if (point.y < bbox.miny())
      return RIGHT | TOP | TWOBITS;
    return RIGHT;
  }
  if (point.y > bbox.maxy())
    return TOP;
  if (point.y < bbox.miny())
    return BOTTOM;
  return INSIDE;
}

template <typename T>
inline uint8_t clip_line(const point<T> &p0, const point<T> &p1,
                         const mapnik::box2d<T> &bbox, point<T> *out_p0,
                         point<T> *out_p1) {
  uint8_t result = OUTBOX;
  *out_p0 = p0;
  *out_p1 = p1;
  int8_t outcode0 = compute_outcode(p0, bbox);
  int8_t outcode1 = compute_outcode(p1, bbox);

  while (true) {
    if (!(outcode0 | outcode1)) {
      result |= INBOX;
      break;
    } else if (outcode0 & outcode1) {
      return OUTBOX;
    }
    T x = 0, y = 0;
    int8_t outcode_out = outcode0 ? outcode0 : outcode1;

    if (outcode_out & BOTTOM) {
      x = out_p0->x +
          (out_p1->x - out_p0->x) * (bbox.maxy() - out_p0->y) /
              (out_p1->y - out_p0->y);
      y = bbox.maxy();
    } else if (outcode_out & TOP) {
      x = out_p0->x +
          (out_p1->x - out_p0->x) * (bbox.miny() - out_p0->y) /
              (out_p1->y - out_p0->y);
      y = bbox.miny();
    } else if (outcode_out & RIGHT) {
      y = out_p0->y +
          (out_p1->y - out_p0->y) * (bbox.maxx() - out_p0->x) /
              (out_p1->x - out_p0->x);
      x = bbox.maxx();
    } else if (outcode_out & LEFT) {
      y = out_p0->y +
          (out_p1->y - out_p0->y) * (bbox.minx() - out_p0->x) /
              (out_p1->x - out_p0->x);
      x = bbox.minx();
    }

    if (outcode_out == outcode0) {
      out_p0->x = x;
      out_p0->y = y;
      outcode0 = compute_outcode(*out_p0, bbox);
      result |= FIRST_CLIPPED;
    } else {
      out_p1->x = x;
      out_p1->y = y;
      outcode1 = compute_outcode(*out_p1, bbox);
    }
  }
  return result;
};

template <typename T>
inline bool clip_line_string(const line_string<T> &line,
                             const mapnik::box2d<T> &bbox,
                             multi_line_string<T> *output_multi_line) {
  if (line.size() < 2) {
    return false;
  }
  bool geometry_inserted = false;
  bool previous_inserted = false;
  auto line_iter = line.begin();
  auto line_end = line.end();
  auto p0 = *line_iter;
  typename multi_line_string<T>::iterator output_line;
  for (++line_iter; line_iter != line_end; ++line_iter) {
    auto p1 = *line_iter;
    point<T> out_p0, out_p1;
    uint8_t clip_result;
    if ((clip_result = clip_line(p0, p1, bbox, &out_p0, &out_p1))) {
      if (!previous_inserted || clip_result & FIRST_CLIPPED) {
        output_multi_line->emplace_back();
        output_line = output_multi_line->end() - 1;
        output_line->push_back(out_p0);
        previous_inserted = true;
        geometry_inserted = true;
      }
      output_line->push_back(out_p1);
    } else {
      previous_inserted = false;
    }
    p0 = p1;
  }
  return geometry_inserted;
}

template <typename T>
inline point<T> get_turning_point(uint8_t maillon_outcode,
                                  const mapnik::box2d<T> &bbox) {
  point<T> result;
  if (maillon_outcode & LEFT) {
    result.x = bbox.minx();
    if (maillon_outcode & TOP)
      result.y = bbox.miny();
    else if (maillon_outcode & BOTTOM)
      result.y = bbox.maxy();
  } else if (maillon_outcode & RIGHT) {
    result.x = bbox.maxx();
    if (maillon_outcode & TOP)
      result.y = bbox.miny();
    else if (maillon_outcode & BOTTOM)
      result.y = bbox.maxy();
  }
  return result;
}

} // namespace bbox_clipper
} // namespace nik
} // namespace flywave

#endif // __FLYWAVE_BBOX_CLIPPER_HH__
