#ifndef REDDATA_TOJSON_H
#define REDDATA_TOJSON_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonObject.h"

namespace RedData::Json {

Red::Handle<JsonObject> to_json(const Red::Handle<Red::IScriptable>& p_object);

}

#endif  //REDDATA_TOJSON_H
