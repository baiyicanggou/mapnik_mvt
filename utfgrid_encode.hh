#pragma once

#include <mapnik/grid/grid.hpp>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <string>

namespace flywave {
namespace nik {
using js_char_type = rapidjson::UTF8<>;
using js_document =
    rapidjson::GenericDocument<js_char_type, rapidjson::CrtAllocator>;
using js_value = rapidjson::GenericValue<js_char_type, rapidjson::CrtAllocator>;

using js_string_buffer = rapidjson::StringBuffer;
using js_writer = rapidjson::Writer<rapidjson::StringBuffer>;

using js_const_array = rapidjson::GenericArray<true, js_value>;
using js_array = rapidjson::GenericArray<false, js_value>;

using js_const_object = rapidjson::GenericObject<true, js_value>;
using js_object = rapidjson::GenericObject<false, js_value>;

extern js_document *local_js_document;

inline std::string to_json(const js_document &root) {
  js_string_buffer buffer;
  js_writer writer(buffer);
  root.Accept(writer);
  return buffer.GetString();
}

std::string encode_utfgrid(const mapnik::grid_view &utfgrid, unsigned size = 4);
} // namespace nik
} // namespace flywave
