#include "JsonNumber.h"

namespace RedData::Json {

JsonNumber::JsonNumber() {
  type = JsonType::Undefined;
  std::memset(value, 0, 8);
}

int64_t JsonNumber::get_int64() const {
  if (type == JsonType::Uint64) {
    return static_cast<int64_t>(*reinterpret_cast<const uint64_t*>(value));
  }

  if (type == JsonType::Double) {
    return static_cast<int64_t>(*reinterpret_cast<const double*>(value));
  }

  return *reinterpret_cast<const int64_t*>(value);
}

uint64_t JsonNumber::get_uint64() const {
  if (type == JsonType::Int64) {
    return static_cast<uint64_t>(*reinterpret_cast<const int64_t*>(value));
  }

  if (type == JsonType::Double) {
    return static_cast<uint64_t>(*reinterpret_cast<const double*>(value));
  }

  return *reinterpret_cast<const uint64_t*>(value);
}

double JsonNumber::get_double() const {
  if (type == JsonType::Int64) {
    return static_cast<double>(*reinterpret_cast<const int64_t*>(value));
  }

  if (type == JsonType::Uint64) {
    return static_cast<double>(*reinterpret_cast<const uint64_t*>(value));
  }

  return *reinterpret_cast<const double*>(value);
}

Red::CString JsonNumber::to_string(const Red::Optional<Red::CString>& p_indent) const {
  if (type == JsonType::Int64) {
    return std::to_string(*reinterpret_cast<const int64_t*>(value));
  }

  if (type == JsonType::Uint64) {
    return std::to_string(*reinterpret_cast<const uint64_t*>(value));
  }

  if (type == JsonType::Double) {
    std::stringstream data;
    data << *reinterpret_cast<const double*>(value);
    return data.str();
  }

  return "";
}

}  // namespace RedData::Json