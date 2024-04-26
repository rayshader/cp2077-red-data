#include "JsonBool.h"

namespace RedData::Json {

JsonBool::JsonBool() : value(false) {
  type = JsonType::Bool;
}

JsonBool::JsonBool(bool p_value) : value(p_value) {
  type = JsonType::Bool;
}

bool JsonBool::get_bool() const {
  return value;
}

Red::CString JsonBool::to_string(
  const Red::Optional<Red::CString>& p_indent) const {
  return value ? "true" : "false";
}

}  // namespace RedData::Json