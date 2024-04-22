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

inline Red::Handle<Red::IScriptable> FromJson(const JsonObject& json,
                                              const Red::CName& type) {
  Red::Handle<Red::IScriptable> handle;

  Red::CallGlobal("RedData.Json.FromJson", handle, json.GetHandle(), type);
  return handle;
}

inline JsonObject ToJson(const Red::Handle<Red::IScriptable>& object) {
  Red::Handle<Red::IScriptable> handle;

  Red::CallGlobal("RedData.Json.ToJson", handle, object);
  return JsonObject(handle);
}

}  // namespace RedData::Json

#endif  //REDDATA_JSON_HPP
