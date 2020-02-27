#ifndef SPHERICAL_MERCATOR_HPP
#define SPHERICAL_MERCATOR_HPP

#ifndef M_PI
#define M_PI 3.141592653589793238462643
#endif

#ifndef RAD_TO_DEG
#define RAD_TO_DEG (180 / M_PI)
#endif

#ifndef DEG_TO_RAD
#define DEG_TO_RAD (M_PI / 180)
#endif

#include <cmath>

namespace flywave {

static const double EARTH_RADIUS = 6378137.0;
static const double EARTH_DIAMETER = EARTH_RADIUS * 2.0;
static const double EARTH_CIRCUMFERENCE = EARTH_DIAMETER * M_PI;
static const double MAXEXTENT = EARTH_CIRCUMFERENCE / 2.0;
static const double M_PI_by2 = M_PI / 2;
static const double D2R = M_PI / 180;
static const double R2D = 180 / M_PI;
static const double M_PIby360 = M_PI / 360;
static const double MAXEXTENTby180 = MAXEXTENT / 180;
static const double MAX_LATITUDE =
    R2D * (2 * std::atan(std::exp(180 * D2R)) - M_PI_by2);

static inline bool lonlat2merc(double *x, double *y, int point_count,
                               double _MAXEXTENTby180 = MAXEXTENTby180) {
  for (int i = 0; i < point_count; ++i) {
    if (x[i] > 180)
      x[i] = 180;
    else if (x[i] < -180)
      x[i] = -180;
    if (y[i] > MAX_LATITUDE)
      y[i] = MAX_LATITUDE;
    else if (y[i] < -MAX_LATITUDE)
      y[i] = -MAX_LATITUDE;
    x[i] = x[i] * _MAXEXTENTby180;
    y[i] = std::log(std::tan((90 + y[i]) * M_PIby360)) * R2D;
    y[i] = y[i] * _MAXEXTENTby180;
  }
  return true;
}

static inline bool merc2lonlat(double *x, double *y, int point_count) {
  for (int i = 0; i < point_count; i++) {
    if (x[i] > MAXEXTENT)
      x[i] = MAXEXTENT;
    else if (x[i] < -MAXEXTENT)
      x[i] = -MAXEXTENT;
    if (y[i] > MAXEXTENT)
      y[i] = MAXEXTENT;
    else if (y[i] < -MAXEXTENT)
      y[i] = -MAXEXTENT;
    x[i] = (x[i] / MAXEXTENT) * 180;
    y[i] = (y[i] / MAXEXTENT) * 180;
    y[i] = R2D * (2 * std::atan(std::exp(y[i] * D2R)) - M_PI_by2);
  }
  return true;
}

template <int levels = 19> class spherical_mercator {
  double Ac[levels];
  double Bc[levels];
  double Cc[levels];
  double zc[levels];

public:
  spherical_mercator(unsigned tile_size) {
    int d, c = tile_size;
    for (d = 0; d < levels; d++) {
      int e = c / 2;
      Bc[d] = c / 360.0;
      Cc[d] = c / (2 * M_PI);
      zc[d] = e;
      Ac[d] = c;
      c *= 2;
    }
  }

  void to_pixels(double &x, double &y, int zoom) {
    double d = zc[zoom];
    double f = minmax(std::sin(DEG_TO_RAD * y), -0.9999, 0.9999);
    x = std::round(d + x * Bc[zoom]);
    y = std::round(d + 0.5 * std::log((1 + f) / (1 - f)) * -Cc[zoom]);
  }

  void from_pixels(double &x, double &y, int zoom) {
    double e = zc[zoom];
    double g = (y - e) / -Cc[zoom];
    x = (x - e) / Bc[zoom];
    y = RAD_TO_DEG * (std::atan(std::exp(g) * 2.0) - 0.5 * M_PI);
  }

private:
  double minmax(double a, double b, double c) {
#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif
    a = MAX(a, b);
    a = MIN(a, c);
    return a;
  }
};
} // namespace flywave
#endif // SPHERICAL_MERCATOR_HPP
