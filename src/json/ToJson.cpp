#include "ToJson.h"
#include "JsonFactory.h"
#include "JsonObject.h"

#include <RED4ext/Scripting/Natives/Generated/red/ResourceReferenceScriptToken.hpp>

namespace RedData::Json {

void object_to_json_set_key(Red::Handle<JsonObject>& p_json,
                            Red::CProperty*& p_prop,
                            const Red::Handle<Red::IScriptable>& p_object);
void array_to_json(Red::Handle<JsonArray>& p_json, Red::CBaseRTTIType* p_type,
                   Red::CProperty*& p_prop,
                   const Red::Handle<Red::IScriptable>& p_object);

Red::Handle<JsonObject> to_json(const Red::Handle<Red::IScriptable>& p_object) {
  if (!p_object) {
    return {};
  }
  Red::Handle<JsonObject> json = JsonFactory::CreateObject();
  Red::CClass* rtti_class = p_object->GetType();

  rtti_class->propsByName.for_each(
    [&json, &p_object](const Red::CName& p_name,
                       Red::CProperty*& p_prop) -> void {
      object_to_json_set_key(json, p_prop, p_object);
    });
  return json;
}

#define SET_KEY(type, set)                                                \
  p_json->set_key_##set(name, p_prop->GetValue<type>(p_object.instance)); \
  return;

void object_to_json_set_key(Red::Handle<JsonObject>& p_json,
                            Red::CProperty*& p_prop,
                            const Red::Handle<Red::IScriptable>& p_object) {
  Red::CName type_name = p_prop->type->GetName();
  Red::CString name = p_prop->name.ToString();

  switch (type_name) {
      // clang-format off
    case Red::GetTypeName<bool>(): SET_KEY(bool, bool)
    case Red::GetTypeName<int8_t>(): SET_KEY(int8_t, int64)
    case Red::GetTypeName<int16_t>(): SET_KEY(int16_t, int64)
    case Red::GetTypeName<int32_t>(): SET_KEY(int32_t, int64)
    case Red::GetTypeName<int64_t>(): SET_KEY(int64_t, int64)
    case Red::GetTypeName<uint8_t>(): SET_KEY(uint8_t, uint64)
    case Red::GetTypeName<uint16_t>(): SET_KEY(uint16_t, uint64)
    case Red::GetTypeName<uint32_t>(): SET_KEY(uint32_t, uint64)
    case Red::GetTypeName<uint64_t>(): SET_KEY(uint64_t, uint64)
    case Red::GetTypeName<float>(): SET_KEY(float, double)
    case Red::GetTypeName<double>(): SET_KEY(double, double)
    case Red::GetTypeName<Red::CString>(): SET_KEY(Red::CString, string)
    case Red::GetTypeName<Red::CName>(): {
      auto value = p_prop->GetValue<Red::CName>(p_object.instance);

      p_json->set_key_string(name, value.ToString());
      return;
    }
    case Red::GetTypeName<Red::ResRef>():
    case Red::GetTypeName<Red::TweakDBID>():
      // NOTE: FNV1a64 is only one way.
      // NOTE: CRC32 is only one way.
      return;
      // clang-format on
  }
  Red::ERTTIType type = p_prop->type->GetType();

  if (type == Red::ERTTIType::Handle) {
    auto inner_object =
      p_prop->GetValue<Red::Handle<Red::IScriptable>>(p_object.instance);

    if (!inner_object) {
      p_json->set_key_null(name);
    } else {
      auto inner_json = to_json(inner_object);

      p_json->set_key(name, inner_json);
    }
    return;
  } else if (type == Red::ERTTIType::WeakHandle) {
    p_json->set_key_null(name);
    return;
  } else if (type == Red::ERTTIType::Array) {
    auto inner_type =
      reinterpret_cast<Red::CRTTIArrayType*>(p_prop->type)->innerType;
    auto inner_json = JsonFactory::CreateArray();

    array_to_json(inner_json, inner_type, p_prop, p_object);
    p_json->set_key(name, inner_json);
  }
}

#define ADD_ITEMS(type, add)                                               \
  {                                                                        \
    auto array = p_prop->GetValue<Red::DynArray<type>>(p_object.instance); \
                                                                           \
    for (const auto& item : array) {                                       \
      p_json->add_item_##add;                                              \
    }                                                                      \
    return;                                                                \
  }

void array_to_json(Red::Handle<JsonArray>& p_json, Red::CBaseRTTIType* p_type,
                   Red::CProperty*& p_prop,
                   const Red::Handle<Red::IScriptable>& p_object) {
  Red::CName type_name = p_type->GetName();

  switch (type_name) {
      // clang-format off
    case Red::GetTypeName<bool>(): ADD_ITEMS(bool, bool(item))
    case Red::GetTypeName<int8_t>(): ADD_ITEMS(int8_t, int64(item))
    case Red::GetTypeName<int16_t>(): ADD_ITEMS(int16_t, int64(item))
    case Red::GetTypeName<int32_t>(): ADD_ITEMS(int32_t, int64(item))
    case Red::GetTypeName<int64_t>(): ADD_ITEMS(int64_t, int64(item))
    case Red::GetTypeName<uint8_t>(): ADD_ITEMS(uint8_t, uint64(item))
    case Red::GetTypeName<uint16_t>(): ADD_ITEMS(uint16_t, uint64(item))
    case Red::GetTypeName<uint32_t>(): ADD_ITEMS(uint32_t, uint64(item))
    case Red::GetTypeName<uint64_t>(): ADD_ITEMS(uint64_t, uint64(item))
    case Red::GetTypeName<float>(): ADD_ITEMS(float, double(item))
    case Red::GetTypeName<double>(): ADD_ITEMS(double, double(item))
    case Red::GetTypeName<Red::CString>(): ADD_ITEMS(Red::CString, string(item))
    case Red::GetTypeName<Red::CName>(): ADD_ITEMS(Red::CName, string(item.ToString()))
    case Red::GetTypeName<Red::ResRef>(): // NOTE: FNV1a64 is only one way.
    case Red::GetTypeName<Red::TweakDBID>(): // NOTE: CRC32 is only one way.
      return;
      // clang-format on
  }
  if (p_type->GetType() == Red::ERTTIType::Handle) {
    auto array = p_prop->GetValue<Red::DynArray<Red::Handle<Red::IScriptable>>>(
      p_object.instance);

    for (const auto& item : array) {
      if (!item) {
        p_json->add_item_null();
      } else {
        p_json->add_item(to_json(item));
      }
    }
    return;
  } else if (p_type->GetType() == Red::ERTTIType::WeakHandle) {
    auto array =
      p_prop->GetValue<Red::DynArray<Red::WeakHandle<Red::IScriptable>>>(
        p_object.instance);

    for (uint32_t i = 0; i < array.size; i++) {
      p_json->add_item_null();
    }
    return;
  } /* else if (p_type->GetType() == Red::ERTTIType::Array) {
    auto inner_type = reinterpret_cast<Red::CRTTIArrayType*>(p_type)->innerType;

    array_to_json(p_json, inner_type, p_prop, p_object);
  }*/
}

}  // namespace RedData::Json

RTTI_DEFINE_GLOBALS({
  RTTI_FUNCTION(RedData::Json::to_json, "RedData.Json.ToJson");
});
