#pragma once

#include "JsonObject.h"

namespace RedData::Json {

Red::Handle<JsonObject> to_json(const Red::Handle<Red::IScriptable>& p_object);

}
