#ifndef REDDATA_JSONBOOL_H
#define REDDATA_JSONBOOL_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData {

class JsonBool : public JsonVariant {
 private:
  bool value;

 public:
  JsonBool();
  explicit JsonBool(bool p_value);

  [[nodiscard]] bool get_bool() const override;

  [[nodiscard]] Red::CString to_string() const override;

  RTTI_IMPL_TYPEINFO(RedData::JsonBool);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData

RTTI_DEFINE_CLASS(RedData::JsonBool, {
  RTTI_ALIAS("RedData.Json.JsonBool");

  RTTI_PARENT(RedData::JsonVariant);

  RTTI_METHOD(get_bool, "GetBool");

  RTTI_METHOD(to_string, "ToString");
});

#endif  //REDDATA_JSONBOOL_H
