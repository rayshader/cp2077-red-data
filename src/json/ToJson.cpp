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

void object_to_json_set_key(Red::Handle<JsonObject>& p_json,
                            Red::CProperty*& p_prop,
                            const Red::Handle<Red::IScriptable>& p_object) {
  Red::CName type_name = p_prop->type->GetName();
  Red::CString name = p_prop->name.ToString();

  switch (type_name) {
    case Red::GetTypeName<bool>():
      p_json->set_key_bool(name, p_prop->GetValue<bool>(p_object.instance));
      return;
    case Red::GetTypeName<int8_t>():
      p_json->set_key_int64(name, p_prop->GetValue<int8_t>(p_object.instance));
      return;
    case Red::GetTypeName<int16_t>():
      p_json->set_key_int64(name, p_prop->GetValue<int16_t>(p_object.instance));
      return;
    case Red::GetTypeName<int32_t>():
      p_json->set_key_int64(name, p_prop->GetValue<int32_t>(p_object.instance));
      return;
    case Red::GetTypeName<int64_t>():
      p_json->set_key_int64(name, p_prop->GetValue<int64_t>(p_object.instance));
      return;
    case Red::GetTypeName<uint8_t>():
      p_json->set_key_uint64(name,
                             p_prop->GetValue<uint8_t>(p_object.instance));
      return;
    case Red::GetTypeName<uint16_t>():
      p_json->set_key_uint64(name,
                             p_prop->GetValue<uint16_t>(p_object.instance));
      return;
    case Red::GetTypeName<uint32_t>():
      p_json->set_key_uint64(name,
                             p_prop->GetValue<uint32_t>(p_object.instance));
      return;
    case Red::GetTypeName<uint64_t>():
      p_json->set_key_uint64(name,
                             p_prop->GetValue<uint64_t>(p_object.instance));
      return;
    case Red::GetTypeName<float>():
      p_json->set_key_double(name, p_prop->GetValue<float>(p_object.instance));
      return;
    case Red::GetTypeName<double>():
      p_json->set_key_double(name, p_prop->GetValue<double>(p_object.instance));
      return;
    case Red::GetTypeName<Red::CString>():
      p_json->set_key_string(name,
                             p_prop->GetValue<Red::CString>(p_object.instance));
      return;
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
    auto inner_type = reinterpret_cast<Red::CRTTIArrayType*>(p_prop->type)->innerType;
    auto inner_json = JsonFactory::CreateArray();

    array_to_json(inner_json, inner_type, p_prop, p_object);
    p_json->set_key(name, inner_json);
  }
}

void array_to_json(Red::Handle<JsonArray>& p_json, Red::CBaseRTTIType* p_type,
                   Red::CProperty*& p_prop,
                   const Red::Handle<Red::IScriptable>& p_object) {
  Red::CName type_name = p_type->GetName();

  switch (type_name) {
    case Red::GetTypeName<bool>(): {
      auto array = p_prop->GetValue<Red::DynArray<bool>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_bool(item);
      }
      return;
    }
    case Red::GetTypeName<int8_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<int8_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_int64(item);
      }
      return;
    }
    case Red::GetTypeName<int16_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<int16_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_int64(item);
      }
      return;
    }
    case Red::GetTypeName<int32_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<int32_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_int64(item);
      }
      return;
    }
    case Red::GetTypeName<int64_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<int64_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_int64(item);
      }
      return;
    }
    case Red::GetTypeName<uint8_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<uint8_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_uint64(item);
      }
      return;
    }
    case Red::GetTypeName<uint16_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<uint16_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_uint64(item);
      }
      return;
    }
    case Red::GetTypeName<uint32_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<uint32_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_uint64(item);
      }
      return;
    }
    case Red::GetTypeName<uint64_t>(): {
      auto array = p_prop->GetValue<Red::DynArray<uint64_t>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_uint64(item);
      }
      return;
    }
    case Red::GetTypeName<float>(): {
      auto array = p_prop->GetValue<Red::DynArray<float>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_double(item);
      }
      return;
    }
    case Red::GetTypeName<double>(): {
      auto array = p_prop->GetValue<Red::DynArray<double>>(p_object.instance);

      for (auto item : array) {
        p_json->add_item_double(item);
      }
      return;
    }
    case Red::GetTypeName<Red::CString>(): {
      auto array =
        p_prop->GetValue<Red::DynArray<Red::CString>>(p_object.instance);

      for (const auto& item : array) {
        p_json->add_item_string(item);
      }
      return;
    }
    case Red::GetTypeName<Red::CName>(): {
      auto array =
        p_prop->GetValue<Red::DynArray<Red::CName>>(p_object.instance);

      for (const auto& item : array) {
        p_json->add_item_string(item.ToString());
      }
      return;
    }
    case Red::GetTypeName<Red::ResRef>():
    case Red::GetTypeName<Red::TweakDBID>():
      // NOTE: FNV1a64 is only one way.
      // NOTE: CRC32 is only one way.
      return;
  }
  if (p_type->GetType() == Red::ERTTIType::Handle) {
    auto array = p_prop->GetValue<Red::DynArray<Red::Handle<Red::IScriptable>>>(
      p_object.instance);
    auto inner_json = JsonFactory::CreateArray();

    for (const auto& item : array) {
      if (!item) {
        inner_json->add_item_null();
      } else {
        inner_json->add_item(to_json(item));
      }
    }
    p_json->add_item(inner_json);
    return;
  } else if (p_type->GetType() == Red::ERTTIType::WeakHandle) {
    auto array =
      p_prop->GetValue<Red::DynArray<Red::WeakHandle<Red::IScriptable>>>(
        p_object.instance);
    auto inner_json = JsonFactory::CreateArray();

    for (uint32_t i = 0; i < array.size; i++) {
      inner_json->add_item_null();
    }
    p_json->add_item(inner_json);
    return;
  } /* else if (p_type->GetType() == Red::ERTTIType::Array) {
    auto inner_type = reinterpret_cast<Red::CRTTIArrayType*>(p_type)->innerType;
    auto inner_json = JsonFactory::CreateArray();

    array_to_json(json, inner_type, p_prop, p_object);
    p_json->add_item(inner_json);
  }*/
}

}  // namespace RedData::Json

RTTI_DEFINE_GLOBALS({
  RTTI_FUNCTION(RedData::Json::to_json, "RedData.Json.ToJson");
});
