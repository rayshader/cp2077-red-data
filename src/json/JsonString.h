#pragma once

#include "JsonVariant.h"

namespace RedData::Json {

class JsonString : public JsonVariant {
  using EscapeRule = std::pair<std::string, std::string>;

  static std::vector<EscapeRule> escape_rules;

  std::string value;

 public:
  JsonString();
  explicit JsonString(std::string p_value);

  [[nodiscard]] Red::CString get_string() const override;

  [[nodiscard]] Red::CString to_string(const Red::Optional<Red::CString>& p_indent) const override;

  RTTI_IMPL_TYPEINFO(RedData::Json::JsonString);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData::Json

RTTI_DEFINE_CLASS(RedData::Json::JsonString, {
  RTTI_ALIAS("RedData.Json.JsonString");

  RTTI_PARENT(RedData::Json::JsonVariant);

  RTTI_METHOD(get_string, "GetString");

  RTTI_METHOD(to_string, "ToString");
});
