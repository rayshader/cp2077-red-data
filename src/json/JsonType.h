#pragma once

namespace RedData::Json {

enum class JsonType {
  Undefined,
  Null,
  Bool,
  Int64,
  Uint64,
  Double,
  String,
  Array,
  Object
};

}

RTTI_DEFINE_ENUM(RedData::Json::JsonType, "RedData.Json.JsonType")
