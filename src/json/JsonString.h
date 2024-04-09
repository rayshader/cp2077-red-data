#ifndef REDDATA_JSONSTRING_H
#define REDDATA_JSONSTRING_H

#include <string>
#include <vector>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData {

class JsonString : public JsonVariant {
 private:
  using EscapeRule = std::pair<std::string, std::string>;
  static std::vector<EscapeRule> escape_rules;

  std::string value;

 public:
  JsonString();
  explicit JsonString(std::string p_value);

  [[nodiscard]] Red::CString get_string() const override;

  [[nodiscard]] Red::CString to_string() const override;

  RTTI_IMPL_TYPEINFO(RedData::JsonString);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData

RTTI_DEFINE_CLASS(RedData::JsonString, {
  RTTI_ALIAS("RedData.Json.JsonString");

  RTTI_PARENT(RedData::JsonVariant);

  RTTI_METHOD(get_string, "GetString");

  RTTI_METHOD(to_string, "ToString");
});

#endif  //REDDATA_JSONSTRING_H
