#pragma once

#include "JsonVariant.h"

namespace RedData::Json {

class JsonNumber : public JsonVariant {
  uint8_t value[8]{};

 public:
  JsonNumber();
  template <typename T>
  explicit JsonNumber(T p_value) {
    type = JsonType::Undefined;
    std::memset(value, 0, 8);
    if constexpr (std::is_same_v<T, int64_t>) {
      type = JsonType::Int64;
      *reinterpret_cast<int64_t*>(value) = p_value;
    } else if constexpr (std::is_same_v<T, uint64_t>) {
      type = JsonType::Uint64;
      *reinterpret_cast<uint64_t*>(value) = p_value;
    } else if constexpr (std::is_same_v<T, double>) {
      type = JsonType::Double;
      *reinterpret_cast<double*>(value) = p_value;
    }
  }

  [[nodiscard]] int64_t get_int64() const override;
  [[nodiscard]] uint64_t get_uint64() const override;
  [[nodiscard]] double get_double() const override;

  [[nodiscard]] Red::CString to_string(const Red::Optional<Red::CString>& p_indent) const override;

  RTTI_IMPL_TYPEINFO(RedData::Json::JsonNumber);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData::Json

RTTI_DEFINE_CLASS(RedData::Json::JsonNumber, {
  RTTI_ALIAS("RedData.Json.JsonNumber");

  RTTI_PARENT(RedData::Json::JsonVariant);

  RTTI_METHOD(get_int64, "GetInt64");
  RTTI_METHOD(get_uint64, "GetUint64");
  RTTI_METHOD(get_double, "GetDouble");

  RTTI_METHOD(to_string, "ToString");
});
