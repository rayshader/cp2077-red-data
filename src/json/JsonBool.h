#pragma once

#include "JsonVariant.h"

namespace RedData::Json {

class JsonBool : public JsonVariant {
  bool value;

 public:
  JsonBool();
  explicit JsonBool(bool p_value);

  [[nodiscard]] bool get_bool() const override;

  [[nodiscard]] Red::CString to_string(const Red::Optional<Red::CString>& p_indent) const override;

  RTTI_IMPL_TYPEINFO(RedData::Json::JsonBool);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData::Json

RTTI_DEFINE_CLASS(RedData::Json::JsonBool, {
  RTTI_ALIAS("RedData.Json.JsonBool");

  RTTI_PARENT(RedData::Json::JsonVariant);

  RTTI_METHOD(get_bool, "GetBool");

  RTTI_METHOD(to_string, "ToString");
});
