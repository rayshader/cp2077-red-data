#ifndef REDDATA_JSONNULL_H
#define REDDATA_JSONNULL_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData {

class JsonNull : public JsonVariant {
 public:
  JsonNull();

  RTTI_IMPL_TYPEINFO(RedData::JsonNull);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedData

RTTI_DEFINE_CLASS(RedData::JsonNull, {
  RTTI_PARENT(RedData::JsonVariant);
});

#endif  //REDDATA_JSONNULL_H
