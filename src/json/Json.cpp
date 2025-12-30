#include "Json.h"
#include "JsonFactory.h"

namespace RedData::Json {

void parse_array(const simdjson::dom::array& p_array,
                 const Red::Handle<JsonArray>& p_root);
void parse_object(const simdjson::dom::object& p_object,
                  const Red::Handle<JsonObject>& p_root);

Red::Handle<JsonVariant> parse_json(const Red::CString& p_json) {
  simdjson::dom::parser parser;
  const auto document = parser.parse(std::string(p_json.c_str()));
  if (document.is_object()) {
    const auto object = simdjson::dom::object(document);
    auto root = JsonFactory::CreateObject();
    parse_object(object, root);
    return root;
  }

  if (document.is_array()) {
    const auto array = simdjson::dom::array(document);
    auto root = JsonFactory::CreateArray();
    parse_array(array, root);
    return root;
  }

  return {};
}

void parse_object(const simdjson::dom::object& p_object,
                  const Red::Handle<JsonObject>& p_root) {
  for (const auto& key_value : p_object) {
    std::string key(key_value.key);
    auto el_value = key_value.value;
    if (el_value.is_bool()) {
      p_root->set_key_bool(key, el_value);
    } else if (el_value.is_int64()) {
      p_root->set_key_int64(key, el_value);
    } else if (el_value.is_uint64()) {
      p_root->set_key_uint64(key, el_value);
    } else if (el_value.is_double()) {
      p_root->set_key_double(key, el_value);
    } else if (el_value.is_string()) {
      p_root->set_key_string(key, std::string(el_value));
    } else if (el_value.is_object()) {
      auto value = JsonFactory::CreateObject();
      auto sub_object = simdjson::dom::object(el_value);

      parse_object(sub_object, value);
      p_root->set_key(key, value);
    } else if (el_value.is_array()) {
      auto value = JsonFactory::CreateArray();
      auto sub_array = simdjson::dom::array(el_value);
      parse_array(sub_array, value);
      p_root->set_key(key, value);
    } else if (el_value.is_null()) {
      p_root->set_key_null(key);
    } else {
      p_root->set_key(key, JsonFactory::CreateUndefined());
    }
  }
}

void parse_array(const simdjson::dom::array& p_array,
                 const Red::Handle<JsonArray>& p_root) {
  for (const auto& item : p_array) {
    if (item.is_bool()) {
      p_root->add_item_bool(item);
    } else if (item.is_int64()) {
      p_root->add_item_int64(item);
    } else if (item.is_uint64()) {
      p_root->add_item_uint64(item);
    } else if (item.is_double()) {
      p_root->add_item_double(item);
    } else if (item.is_string()) {
      p_root->add_item_string(std::string(item));
    } else if (item.is_object()) {
      auto value = JsonFactory::CreateObject();
      auto sub_object = simdjson::dom::object(item);
      parse_object(sub_object, value);
      p_root->add_item(value);
    } else if (item.is_array()) {
      auto value = JsonFactory::CreateArray();
      auto sub_array = simdjson::dom::array(item);
      parse_array(sub_array, value);
      p_root->add_item(value);
    } else if (item.is_null()) {
      p_root->add_item_null();
    } else {
      p_root->add_item(JsonFactory::CreateUndefined());
    }
  }
}

}  // namespace RedData::Json

RTTI_DEFINE_GLOBALS({
  RTTI_FUNCTION(RedData::Json::parse_json, "RedData.Json.ParseJson");
});
