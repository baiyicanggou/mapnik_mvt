#pragma once

#include <mapnik/layer.hpp>
#include <mapnik/map.hpp>

#include "source.hh"
#include "tile.hh"
#include "util.hh"

#include <set>
#include <unordered_map>
#include <vector>

namespace flywave {
namespace nik {

struct map_option {
  std::string name;
  mapnik::Map *map;
};

using map_options = std::vector<map_option>;

struct layer_info {
  std::string name;
  std::string source;
};

using layer_infos_type = std::unordered_map<std::string, layer_info>;

struct map_data {
  map_data(mapnik::Map *m) : map(*m) {}
  mapnik::Map map;
  layer_infos_type layer_info_map;
};

class mapnik_source : public nik::source {
public:
  mapnik_source(map_options &options) { init(options); }

  virtual ~mapnik_source() {}

  void active_layer(const std::string &style, std::set<std::string> *layers);

  inline mapnik::Map &map(const std::string &style) {
    return (_maps[style]->map);
  }

  void add_datasource(const std::string &name, mapnik::datasource_ptr ptr) {
    _datasources.emplace(name, ptr);
  }

  void set_current_style(const std::string &style) { current_style_ = style; }

protected:
  void init(map_options &options) noexcept;

  std::shared_ptr<map_data> load_map(const map_option &sinfo);

  std::unordered_map<std::string, std::shared_ptr<map_data>> _maps;

  std::unordered_map<std::string, mapnik::datasource_ptr> _datasources;

  bool done_;

  std::string current_style_;
};
} // namespace nik
} // namespace flywave
