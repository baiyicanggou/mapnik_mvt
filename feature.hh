#pragma once

#include <mapnik/datasource.hpp>
#include <mapnik/geometry_adapters.hpp>

#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace flywave {
namespace nik {

struct value;

struct null_value_t {
  constexpr null_value_t() {}
  constexpr null_value_t(std::nullptr_t) {}
};

constexpr bool operator==(const null_value_t &, const null_value_t &) {
  return true;
}

constexpr bool operator!=(const null_value_t &, const null_value_t &) {
  return false;
}

constexpr bool operator<(const null_value_t &, const null_value_t &) {
  return false;
}

constexpr null_value_t null_value = null_value_t();

using value_base = boost::variant<
    null_value_t, bool, uint64_t, int64_t, double, std::string,
    boost::recursive_wrapper<std::vector<value>>,
    boost::recursive_wrapper<std::unordered_map<std::string, value>>>;

struct value : value_base {
  using value_base::value_base;
};

using property_map = std::unordered_map<std::string, value>;

using identifier = boost::variant<uint64_t, int64_t, double, std::string>;

template <class T> struct feature {
  using coordinate_type = T;
  using geometry_type = mapnik::geometry::geometry<T>;

  geometry_type geometry;
  property_map properties{};
  boost::optional<identifier> id{};

  feature(geometry_type geometry_, property_map properties_ = property_map{},
          boost::optional<identifier> id_ = boost::optional<identifier>{})
      : geometry(std::move(geometry_)), properties(std::move(properties_)),
        id(std::move(id_)) {}
};

template <class T>
constexpr bool operator==(feature<T> const &lhs, feature<T> const &rhs) {
  return lhs.id == rhs.id && lhs.geometry == rhs.geometry &&
         lhs.properties == rhs.properties;
}

template <class T>
constexpr bool operator!=(feature<T> const &lhs, feature<T> const &rhs) {
  return !(lhs == rhs);
}

template <class T, template <typename...> class Cont = std::vector>
struct feature_collection : Cont<feature<T>> {
  using coordinate_type = T;
  using feature_type = feature<T>;
  using container_type = Cont<feature_type>;
  using container_type::container_type;
};
} // namespace nik
} // namespace flywave