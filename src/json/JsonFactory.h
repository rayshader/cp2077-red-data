#pragma once

#include "JsonArray.h"
#include "JsonBool.h"
#include "JsonNull.h"
#include "JsonNumber.h"
#include "JsonObject.h"
#include "JsonString.h"
#include "JsonVariant.h"

namespace RedData::Json {

class JsonFactory {
 public:
  static Red::Handle<JsonUndefined> CreateUndefined() {
    return Red::MakeHandle<JsonUndefined>();
  }

  static Red::Handle<JsonNull> CreateNull() {
    return Red::MakeHandle<JsonNull>();
  }

  static Red::Handle<JsonBool> CreateBool(
    const simdjson::dom::element& p_value) {
    return Create<bool, JsonBool>(p_value);
  }

  static Red::Handle<JsonBool> CreateBool(const bool p_value) {
    return Create<bool, JsonBool>(p_value);
  }

  static Red::Handle<JsonNumber> CreateInt64(
    const simdjson::dom::element& p_value) {
    return Create<int64_t, JsonNumber>(p_value);
  }

  static Red::Handle<JsonNumber> CreateInt64(const int64_t p_value) {
    return Create<int64_t, JsonNumber>(p_value);
  }

  static Red::Handle<JsonNumber> CreateUint64(
    const simdjson::dom::element& p_value) {
    return Create<uint64_t, JsonNumber>(p_value);
  }

  static Red::Handle<JsonNumber> CreateUint64(const uint64_t p_value) {
    return Create<uint64_t, JsonNumber>(p_value);
  }

  static Red::Handle<JsonNumber> CreateDouble(
    const simdjson::dom::element& p_value) {
    return Create<double, JsonNumber>(p_value);
  }

  static Red::Handle<JsonNumber> CreateDouble(const double p_value) {
    return Create<double, JsonNumber>(p_value);
  }

  static Red::Handle<JsonString> CreateString(
    const simdjson::dom::element& p_value) {
    return Create<std::string, JsonString>(p_value);
  }

  static Red::Handle<JsonString> CreateString(std::string p_value) {
    return Create<std::string, JsonString>(std::move(p_value));
  }

  static Red::Handle<JsonArray> CreateArray() {
    return Red::MakeHandle<JsonArray>();
  }

  static Red::Handle<JsonObject> CreateObject() {
    return Red::MakeHandle<JsonObject>();
  }

  template <typename T, class U>
  static Red::Handle<U> Create(const simdjson::dom::element& p_value) {
    return Red::MakeHandle<U>(T(p_value));
  }

  template <typename T, class U>
  static Red::Handle<U> Create(T p_value) {
    return Red::MakeHandle<U>(std::move(p_value));
  }
};

}  // namespace RedData::Json
