#ifndef REDDATA_JSONTYPE_H
#define REDDATA_JSONTYPE_H

#include <RedLib.hpp>

namespace RedData::Json {

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

RTTI_DEFINE_ENUM(RedData::Json::JsonType);

#endif  //REDDATA_JSONTYPE_H
