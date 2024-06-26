#include "JsonVariant.h"
#include "JsonArray.h"
#include "JsonObject.h"

namespace RedData::Json {

JsonVariant::JsonVariant() : type(JsonType::Undefined) {}

bool JsonVariant::is_indent_illegal(const std::string& p_indent) {
  for (const char& c : p_indent) {
    if (c != ' ' && c != '\t') {
      return true;
    }
  }
  return false;
}

std::string JsonVariant::to_json(const JsonVariant* p_json,
                                 const std::string& p_current_indent,
                                 const std::string& p_indent) {
  if (p_json == nullptr) {
    return "";
  }
  if (p_json->is_object()) {
    return JsonObject::to_json(dynamic_cast<const JsonObject*>(p_json),
                               p_current_indent, p_indent);
  } else if (p_json->is_array()) {
    return JsonArray::to_json(dynamic_cast<const JsonArray*>(p_json),
                              p_current_indent, p_indent);
  } else {
    return p_json->to_string({}).c_str();
  }
}

bool JsonVariant::is_undefined() const {
  return type == JsonType::Undefined;
}

bool JsonVariant::is_null() const {
  return type == JsonType::Null;
}

bool JsonVariant::is_bool() const {
  return type == JsonType::Bool;
}

bool JsonVariant::is_int64() const {
  return type == JsonType::Int64;
}

bool JsonVariant::is_uint64() const {
  return type == JsonType::Uint64;
}

bool JsonVariant::is_double() const {
  return type == JsonType::Double;
}

bool JsonVariant::is_string() const {
  return type == JsonType::String;
}

bool JsonVariant::is_array() const {
  return type == JsonType::Array;
}

bool JsonVariant::is_object() const {
  return type == JsonType::Object;
}

bool JsonVariant::get_bool() const {
  return false;
}

int64_t JsonVariant::get_int64() const {
  return 0;
}

uint64_t JsonVariant::get_uint64() const {
  return 0;
}

double JsonVariant::get_double() const {
  return 0;
}

Red::CString JsonVariant::get_string() const {
  return {};
}

Red::CString JsonVariant::to_string(
  const Red::Optional<Red::CString>& p_indent) const {
  if (type == JsonType::Null) {
    return "null";
  }
  return "<undefined>";
}

}  // namespace RedData::Json