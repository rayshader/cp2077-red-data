#ifndef REDDATA_FROMJSON_H
#define REDDATA_FROMJSON_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonObject.h"

namespace RedData::Json {

Red::Handle<Red::IScriptable> from_json(const Red::Handle<JsonObject>& p_json,
                                        const Red::CName& p_type);

}

#endif  //REDDATA_FROMJSON_H
