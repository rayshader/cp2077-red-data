#ifndef REDDATA_JSON_HPP
#define REDDATA_JSON_HPP

#include <RedLib.hpp>

#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonVariant.hpp"

namespace RedData::Json {

inline JsonVariant ParseJson(const Red::CString& text) {
  Red::Handle<Red::IScriptable> handle;

  Red::CallGlobal("RedData.Json.ParseJson", handle, text);
  return JsonVariant(handle);
}

template <class T = Red::IScriptable>
inline Red::Handle<T> FromJson(const JsonObject& json, Red::CName type = {}) {
  Red::Handle<Red::IScriptable> handle;

  if constexpr (!std::is_same<T, Red::IScriptable>()) {
    type = Red::GetTypeName<T>();
  }
  Red::CallGlobal("RedData.Json.FromJson", handle, json.GetHandle(), type);
  return Red::AsHandle<T>(handle.GetPtr<T>());
}

inline JsonObject ToJson(const Red::Handle<Red::IScriptable>& object) {
  Red::Handle<Red::IScriptable> handle;

  Red::CallGlobal("RedData.Json.ToJson", handle, object);
  return JsonObject(handle);
}

}  // namespace RedData::Json

#endif  //REDDATA_JSON_HPP
