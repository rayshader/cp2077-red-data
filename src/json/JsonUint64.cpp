#include "JsonUint64.h"

namespace RedData::Json {

JsonUint64::JsonUint64() : value(0) {
  type = JsonType::Uint64;
}

JsonUint64::JsonUint64(uint64_t p_value) : value(p_value) {
  type = JsonType::Uint64;
}

uint64_t JsonUint64::get_uint64() const {
  return value;
}

Red::CString JsonUint64::to_string(
  const Red::Optional<Red::CString>& p_indent) const {
  return std::to_string(value);
}

}  // namespace RedData::Json