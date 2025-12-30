#include "JsonObject.h"
#include "JsonFactory.h"

namespace RedData::Json {

JsonObject::JsonObject() {
  type = JsonType::Object;
}

std::string JsonObject::to_json(const JsonObject* p_object,
                                const std::string& p_current_indent,
                                const std::string& p_indent) {
  const bool is_pretty = !p_indent.empty();
  const std::string inner_indent = p_current_indent + p_indent;
  const auto keys = p_object->get_string_keys();
  std::string json = "{";

  for (int i = 0; i < keys.size(); i++) {
    auto key = keys[i];
    auto value = p_object->get_key(key);
    if (is_pretty) {
      json.append("\n");
      json.append(inner_indent);
    }

    json.append("\"");
    json.append(key);
    json.append("\":");

    if (is_pretty) {
      json.append(" ");
    }

    json.append(JsonVariant::to_json(value, inner_indent, p_indent));

    if (i + 1 < keys.size()) {
      json.append(",");
    }
  }

  if (!keys.empty() && is_pretty) {
    json.append("\n");
  }

  if (is_pretty) {
    json.append(p_current_indent);
  }

  json.append("}");
  return json;
}

Red::DynArray<Red::CString> JsonObject::get_keys() const {
  Red::DynArray<Red::CString> keys;
  for (const auto& key: fields | std::views::keys) {
    keys.PushBack(key);
  }
  return keys;
}

Red::DynArray<Red::Handle<JsonVariant>> JsonObject::get_values() const {
  Red::DynArray<Red::Handle<JsonVariant>> keys;
  for (const auto& value: fields | std::views::values) {
    keys.PushBack(value);
  }
  return keys;
}

bool JsonObject::has_key(const Red::CString& p_key) const {
  return fields.contains(p_key.c_str());
}

Red::Handle<JsonVariant> JsonObject::get_key(const Red::CString& p_key) const {
  const std::string key = p_key.c_str();
  const auto it = fields.find(key);
  if (it == fields.end()) {
    return {};
  }

  return it->second;
}

void JsonObject::set_key(const Red::CString& p_key,
                         const Red::Handle<JsonVariant>& p_value) {
  fields[p_key.c_str()] = p_value;
}

void JsonObject::remove_key(const Red::CString& p_key) {
  fields.erase(p_key.c_str());
}

bool JsonObject::get_key_bool(const Red::CString& p_key) const {
  const std::string key = p_key.c_str();
  const auto it = fields.find(key);
  if (it == fields.end()) {
    return {};
  }

  return it->second->get_bool();
}

int64_t JsonObject::get_key_int64(const Red::CString& p_key) const {
  const std::string key = p_key.c_str();
  const auto it = fields.find(key);
  if (it == fields.end()) {
    return {};
  }

  return it->second->get_uint64();
}

uint64_t JsonObject::get_key_uint64(const Red::CString& p_key) const {
  const std::string key = p_key.c_str();
  const auto it = fields.find(key);
  if (it == fields.end()) {
    return {};
  }

  return it->second->get_uint64();
}

double JsonObject::get_key_double(const Red::CString& p_key) const {
  const std::string key = p_key.c_str();
  const auto it = fields.find(key);
  if (it == fields.end()) {
    return {};
  }

  return it->second->get_double();
}

Red::CString JsonObject::get_key_string(const Red::CString& p_key) const {
  const std::string key = p_key.c_str();
  const auto it = fields.find(key);
  if (it == fields.end()) {
    return {};
  }

  return it->second->get_string();
}

void JsonObject::set_key_null(const Red::CString& p_key) {
  set_key(p_key, JsonFactory::CreateNull());
}

void JsonObject::set_key_bool(const Red::CString& p_key, const bool p_value) {
  set_key(p_key, JsonFactory::CreateBool(p_value));
}

void JsonObject::set_key_int64(const Red::CString& p_key, const int64_t p_value) {
  set_key(p_key, JsonFactory::CreateInt64(p_value));
}

void JsonObject::set_key_uint64(const Red::CString& p_key, const uint64_t p_value) {
  set_key(p_key, JsonFactory::CreateUint64(p_value));
}

void JsonObject::set_key_double(const Red::CString& p_key, const double p_value) {
  set_key(p_key, JsonFactory::CreateDouble(p_value));
}

void JsonObject::set_key_string(const Red::CString& p_key,
                                const Red::CString& p_value) {
  set_key(p_key, JsonFactory::CreateString(p_value.c_str()));
}

void JsonObject::clear() {
  fields.clear();
}

Red::CString JsonObject::to_string(
  const Red::Optional<Red::CString>& p_indent) const {
  std::string indent = p_indent.value.c_str();
  if (is_indent_illegal(indent)) {
    indent = "";
  }

  return to_json(this, "", indent);
}

std::vector<std::string> JsonObject::get_string_keys() const {
  std::vector<std::string> keys;
  for (const auto& key: fields | std::views::keys) {
    keys.push_back(key);
  }
  return keys;
}

}  // namespace RedData::Json