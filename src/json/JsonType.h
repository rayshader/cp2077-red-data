#ifndef REDDATA_JSONTYPE_H
#define REDDATA_JSONTYPE_H

#include <RedLib.hpp>

namespace RedData {

enum class JsonType {
  Undefined,
  Null,
  Bool,
  Int64,
  Double,
  String,
  Array,
  Object
};

}

RTTI_DEFINE_ENUM(RedData::JsonType);

#endif  //REDDATA_JSONTYPE_H
