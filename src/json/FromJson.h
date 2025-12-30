#pragma once

#include "JsonObject.h"

namespace RedData::Json {

Red::Handle<Red::IScriptable> from_json(const Red::Handle<JsonObject>& p_json,
                                        const Red::CName& p_type);

}
