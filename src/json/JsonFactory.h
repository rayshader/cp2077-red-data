#ifndef REDDATA_JSONFACTORY_H
#define REDDATA_JSONFACTORY_H

#include <simdjson.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>
#include <utility>

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
  inline static Red::Handle<JsonUndefined> CreateUndefined() {
    return Red::MakeHandle<JsonUndefined>();
  }

  inline static Red::Handle<JsonNull> CreateNull() {
    return Red::MakeHandle<JsonNull>();
  }

  inline static Red::Handle<JsonBool> CreateBool(
    const simdjson::dom::element& p_value) {
    return Create<bool, JsonBool>(p_value);
  }

  inline static Red::Handle<JsonBool> CreateBool(bool p_value) {
    return Create<bool, JsonBool>(p_value);
  }

  inline static Red::Handle<JsonNumber> CreateInt64(
    const simdjson::dom::element& p_value) {
    return Create<int64_t, JsonNumber>(p_value);
  }

  inline static Red::Handle<JsonNumber> CreateInt64(int64_t p_value) {
    return Create<int64_t, JsonNumber>(p_value);
  }

  inline static Red::Handle<JsonNumber> CreateUint64(
    const simdjson::dom::element& p_value) {
    return Create<uint64_t, JsonNumber>(p_value);
  }

  inline static Red::Handle<JsonNumber> CreateUint64(uint64_t p_value) {
    return Create<uint64_t, JsonNumber>(p_value);
  }

  inline static Red::Handle<JsonNumber> CreateDouble(
    const simdjson::dom::element& p_value) {
    return Create<double, JsonNumber>(p_value);
  }

  inline static Red::Handle<JsonNumber> CreateDouble(double p_value) {
    return Create<double, JsonNumber>(p_value);
  }

  inline static Red::Handle<JsonString> CreateString(
    const simdjson::dom::element& p_value) {
    return Create<std::string, JsonString>(p_value);
  }

  inline static Red::Handle<JsonString> CreateString(std::string p_value) {
    return Create<std::string, JsonString>(std::move(p_value));
  }

  inline static Red::Handle<JsonArray> CreateArray() {
    return Red::MakeHandle<JsonArray>();
  }

  inline static Red::Handle<JsonObject> CreateObject() {
    return Red::MakeHandle<JsonObject>();
  }

  template <typename T, class U>
  inline static Red::Handle<U> Create(const simdjson::dom::element& p_value) {
    return Red::MakeHandle<U>(T(p_value));
  }

  template <typename T, class U>
  inline static Red::Handle<U> Create(T p_value) {
    return Red::MakeHandle<U>(std::move(p_value));
  }
};

}  // namespace RedData::Json

#endif  //REDDATA_JSONFACTORY_H
