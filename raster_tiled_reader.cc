#include "raster_tiled_reader.hh"
#include "raster_data.hh"

namespace flywave {
namespace nik {

template <typename Image>
void copy_image(Image const &src, Image &dst, unsigned x, unsigned y,
                unsigned width, unsigned height) {
  for (int i = x; i < width; i++) {
    for (int j = y; j < height; j++) {
      dst(x, y) = src(x, y);
    }
  }
}

mapnik::image_any raster_tiled_reader::read(unsigned x, unsigned y,
                                            unsigned width,
                                            unsigned height) const {
  if (x == 0 && y == 0 && width == _data->data().width() &&
      height == _data->data().height()) {
    return _data->data();
  }
  bool premultiplied = _data->data().get_premultiplied();
  bool painted = _data->data().painted();
  mapnik::image_dtype dtype = _data->data().get_dtype();
  switch (dtype) {
  case mapnik::image_dtype_gray8: {
    auto img = mapnik::image_gray8(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray8>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray8s: {
    auto img =
        mapnik::image_gray8s(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray8s>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray16: {
    auto img =
        mapnik::image_gray16(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray16>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray16s: {
    auto img =
        mapnik::image_gray16s(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray16s>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray32: {
    auto img =
        mapnik::image_gray32(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray32>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray32s: {
    auto img =
        mapnik::image_gray32s(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray32s>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray32f: {
    auto img =
        mapnik::image_gray32f(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray32f>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray64: {
    auto img =
        mapnik::image_gray64(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray64>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray64s: {
    auto img =
        mapnik::image_gray64s(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray64s>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_gray64f: {
    auto img =
        mapnik::image_gray64f(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_gray64f>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  case mapnik::image_dtype_null:
    return mapnik::image_any(mapnik::image_null());
  case mapnik::image_dtype_rgba8:
  case mapnik::IMAGE_DTYPE_MAX:
  default: {
    auto img = mapnik::image_rgba8(width, height, true, premultiplied, painted);
    copy_image(_data->template get<mapnik::image_rgba8>(), img, x, y, width,
               height);
    return mapnik::image_any(img);
  }
  }
}

} // namespace nik
} // namespace flywave