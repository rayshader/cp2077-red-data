#ifndef REDDATA_JSONDOUBLE_H
#define REDDATA_JSONDOUBLE_H

#include <cstdint>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData::Json {

class JsonDouble : public JsonVariant {
 private:
  double value;

 public:
  JsonDouble();
  explicit JsonDouble(double p_value);

  [[nodiscard]] double get_double() const override;

  [[nodiscard]] Red::CString to_string(
    const Red::Optional<Red::CString>& p_indent) const override;

  RTTI_IMPL_TYPEINFO(RedData::Json::JsonDouble);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData::Json

RTTI_DEFINE_CLASS(RedData::Json::JsonDouble, {
  RTTI_ALIAS("RedData.Json.JsonDouble");

  RTTI_PARENT(RedData::Json::JsonVariant);

  RTTI_METHOD(get_double, "GetDouble");

  RTTI_METHOD(to_string, "ToString");
});

#endif  //REDDATA_JSONDOUBLE_H
