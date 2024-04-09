#include <simdjson.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.h"

namespace RedData::Json {

Red::Handle<JsonVariant> parse_json(const Red::CString& p_json);

}  // namespace RedData::Json
