#pragma once

#include "JsonVariant.h"

namespace RedData::Json {

class JsonNull : public JsonVariant {
 public:
  JsonNull();

  RTTI_IMPL_TYPEINFO(RedData::Json::JsonNull);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData::Json

RTTI_DEFINE_CLASS(RedData::Json::JsonNull, {
  RTTI_ALIAS("RedData.Json.JsonNull");

  RTTI_PARENT(RedData::Json::JsonVariant);
});
