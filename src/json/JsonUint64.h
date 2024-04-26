#ifndef REDDATA_JSONUINT64_H
#define REDDATA_JSONUINT64_H

#include <cstdint>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData::Json {

class JsonUint64 : public JsonVariant {
 private:
  uint64_t value;

 public:
  JsonUint64();
  explicit JsonUint64(uint64_t p_value);

  [[nodiscard]] uint64_t get_uint64() const override;

  [[nodiscard]] Red::CString to_string(
    const Red::Optional<Red::CString>& p_indent) const override;

  RTTI_IMPL_TYPEINFO(RedData::Json::JsonUint64);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData::Json

RTTI_DEFINE_CLASS(RedData::Json::JsonUint64, {
  RTTI_ALIAS("RedData.Json.JsonUint64");

  RTTI_PARENT(RedData::Json::JsonVariant);

  RTTI_METHOD(get_uint64, "GetUint64");

  RTTI_METHOD(to_string, "ToString");
});

#endif  //REDDATA_JSONUINT64_H
