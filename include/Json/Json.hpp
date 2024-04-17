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

}  // namespace RedData::Json

#endif  //REDDATA_JSON_HPP
