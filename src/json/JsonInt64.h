#ifndef REDDATA_JSONINT64_H
#define REDDATA_JSONINT64_H

#include <cstdint>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData {

class JsonInt64 : public JsonVariant {
 private:
  int64_t value;

 public:
  JsonInt64();
  explicit JsonInt64(int64_t p_value);

  [[nodiscard]] int64_t get_int64() const override;

  [[nodiscard]] Red::CString to_string() const override;

  RTTI_IMPL_TYPEINFO(RedData::JsonInt64);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData

RTTI_DEFINE_CLASS(RedData::JsonInt64, {
  RTTI_ALIAS("RedData.Json.JsonInt64");

  RTTI_PARENT(RedData::JsonVariant);

  RTTI_METHOD(get_int64, "GetInt64");

  RTTI_METHOD(to_string, "ToString");
});

#endif  //REDDATA_JSONINT64_H
