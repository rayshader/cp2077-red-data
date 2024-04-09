#ifndef REDDATA_JSONNULL_H
#define REDDATA_JSONNULL_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData::Json {

class JsonNull : public JsonVariant {
 public:
  JsonNull();

  RTTI_IMPL_TYPEINFO(RedData::Json::JsonNull);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData::Json

RTTI_DEFINE_CLASS(RedData::Json::JsonNull,
                  { RTTI_PARENT(RedData::Json::JsonVariant); });

#endif  //REDDATA_JSONNULL_H
