#pragma once

#include "JsonVariant.h"

namespace RedData::Json {

Red::Handle<JsonVariant> parse_json(const Red::CString& p_json);

}  // namespace RedData::Json
