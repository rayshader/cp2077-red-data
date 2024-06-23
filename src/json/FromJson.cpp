#include "FromJson.h"
#include "JsonObject.h"

#include <RED4ext/Scripting/Natives/Generated/red/ResourceReferenceScriptToken.hpp>

namespace RedData::Json {

void object_from_json(const JsonObject*& p_json,
                      Red::Handle<Red::IScriptable>& p_object);
void object_from_json_set_property(const Red::Handle<JsonVariant>& p_field,
                                   Red::CProperty*& p_prop,
                                   Red::Handle<Red::IScriptable>& p_object);

void array_from_json(const JsonArray*& p_json, Red::CBaseRTTIType* p_type,
                     Red::CProperty*& p_prop,
                     Red::Handle<Red::IScriptable>& p_object);
template <typename T>
void array_from_json_fill(const JsonArray*& p_json, Red::DynArray<T>& p_array,
                          Red::CBaseRTTIType* p_inner_type = nullptr);

Red::Handle<Red::IScriptable> from_json(const Red::Handle<JsonObject>& p_json,
                                        const Red::CName& p_type) {
  if (!p_json || !p_json->is_object() || p_json->is_null()) {
    return {};
  }
  if (p_type.IsNone() || Red::GetClass(p_type) == nullptr) {
    return {};
  }
  Red::Handle<Red::IScriptable> object = Red::MakeScriptedHandle(p_type);
  const auto* json = p_json.GetPtr<const JsonObject>();

  object_from_json(json, object);
  return object;
}

void object_from_json(const JsonObject*& p_json,
                      Red::Handle<Red::IScriptable>& p_object) {
  Red::CClass* rtti_class = p_object->GetType();

  rtti_class->propsByName.for_each(
    [&p_object, &p_json](const Red::CName& p_name,
                         Red::CProperty*& p_prop) -> void {
      Red::CString key = p_name.ToString();

      if (!p_json->has_key(key)) {
        return;
      }
      object_from_json_set_property(p_json->get_key(key), p_prop, p_object);
    });
}

#define FILL_ARRAY(type)                        \
  {                                             \
    Red::DynArray<type> array;                  \
                                                \
    array_from_json_fill(p_json, array);        \
    p_prop->SetValue(p_object.instance, array); \
    return;                                     \
  }

void array_from_json(const JsonArray*& p_json, Red::CBaseRTTIType* p_type,
                     Red::CProperty*& p_prop,
                     Red::Handle<Red::IScriptable>& p_object) {
  Red::CName type_name = p_type->GetName();

  switch (type_name) {
      // clang-format off
    case Red::GetTypeName<bool>(): FILL_ARRAY(bool)
    case Red::GetTypeName<int8_t>(): FILL_ARRAY(int8_t)
    case Red::GetTypeName<int16_t>(): FILL_ARRAY(int16_t)
    case Red::GetTypeName<int32_t>(): FILL_ARRAY(int32_t)
    case Red::GetTypeName<int64_t>(): FILL_ARRAY(int64_t)
    case Red::GetTypeName<uint8_t>(): FILL_ARRAY(uint8_t)
    case Red::GetTypeName<uint16_t>(): FILL_ARRAY(uint16_t)
    case Red::GetTypeName<uint32_t>(): FILL_ARRAY(uint32_t)
    case Red::GetTypeName<uint64_t>(): FILL_ARRAY(uint64_t)
    case Red::GetTypeName<float>(): FILL_ARRAY(float)
    case Red::GetTypeName<double>(): FILL_ARRAY(double)
    case Red::GetTypeName<Red::CString>(): FILL_ARRAY(Red::CString)
    case Red::GetTypeName<Red::CName>(): FILL_ARRAY(Red::CName)
    case Red::GetTypeName<Red::ResRef>(): FILL_ARRAY(Red::ResRef)
    case Red::GetTypeName<Red::TweakDBID>(): FILL_ARRAY(Red::TweakDBID)
      // clang-format on
  }
  if (p_type->GetType() == Red::ERTTIType::Handle) {
    auto inner_type =
      reinterpret_cast<Red::CRTTIHandleType*>(p_type)->innerType;
    Red::DynArray<Red::Handle<Red::IScriptable>> array;

    array_from_json_fill(p_json, array, inner_type);
    p_prop->SetValue(p_object.instance, array);
  } else if (p_type->GetType() == Red::ERTTIType::WeakHandle) {
    Red::DynArray<Red::WeakHandle<Red::IScriptable>> array;

    array_from_json_fill(p_json, array);
    p_prop->SetValue(p_object.instance, array);
  } /* else if (p_type->GetType() == Red::ERTTIType::Array) {
    auto inner_type = reinterpret_cast<Red::CRTTIArrayType*>(p_type)->innerType;
    auto array;

    p_prop->SetValue(p_object.instance, array);
  }*/
}

#define GET_KEY(type, get)                                   \
  p_prop->SetValue(p_object.instance,                        \
                   static_cast<type>(p_field->get_##get())); \
  return;

void object_from_json_set_property(const Red::Handle<JsonVariant>& p_field,
                                   Red::CProperty*& p_prop,
                                   Red::Handle<Red::IScriptable>& p_object) {
  Red::CName type_name = p_prop->type->GetName();
  auto type = p_prop->type;

  switch (type_name) {
      // clang-format off
    case Red::GetTypeName<bool>(): GET_KEY(bool, bool)
    case Red::GetTypeName<int8_t>(): GET_KEY(int8_t, int64)
    case Red::GetTypeName<int16_t>(): GET_KEY(int16_t, int64)
    case Red::GetTypeName<int32_t>(): GET_KEY(int32_t, int64)
    case Red::GetTypeName<int64_t>(): GET_KEY(int64_t, int64)
    case Red::GetTypeName<uint8_t>(): GET_KEY(uint8_t, uint64)
    case Red::GetTypeName<uint16_t>(): GET_KEY(uint16_t, uint64)
    case Red::GetTypeName<uint32_t>(): GET_KEY(uint32_t, uint64)
    case Red::GetTypeName<uint64_t>(): GET_KEY(uint64_t, uint64)
    case Red::GetTypeName<float>(): GET_KEY(float, double)
    case Red::GetTypeName<double>(): GET_KEY(double, double)
    case Red::GetTypeName<Red::CString>(): GET_KEY(Red::CString, string)
    case Red::GetTypeName<Red::CName>():
      p_prop->SetValue(p_object.instance,
                       Red::CName(p_field->get_string().c_str()));
      return;
    case Red::GetTypeName<Red::ResRef>(): {
      Red::ResRef res_ref;

      res_ref.resource = Red::RaRef<Red::CResource>(
        Red::ResourcePath(p_field->get_string().c_str()));
      p_prop->SetValue(p_object.instance, res_ref);
      return;
    }
    case Red::GetTypeName<Red::TweakDBID>():
      p_prop->SetValue(p_object, Red::TweakDBID(p_field->get_string().c_str()));
      return;
      // clang-format on
  }
  if (type->GetType() == Red::ERTTIType::Handle) {
    if (!p_field->is_object() || p_field->is_null()) {
      Red::Handle<Red::IScriptable> empty;

      p_prop->SetValue(p_object.instance, empty);
    } else {
      auto inner_type =
        reinterpret_cast<Red::CRTTIHandleType*>(type)->innerType;
      auto inner_object = Red::MakeScriptedHandle(inner_type->GetName());
      auto inner_json = p_field.GetPtr<const JsonObject>();

      object_from_json(inner_json, inner_object);
      p_prop->SetValue(p_object.instance, inner_object);
    }
    return;
  } else if (type->GetType() == Red::ERTTIType::WeakHandle) {
    Red::WeakHandle<Red::IScriptable> empty;

    p_prop->SetValue(p_object.instance, empty);
    return;
  } else if (type->GetType() == Red::ERTTIType::Array && p_field->is_array()) {
    auto inner_type = reinterpret_cast<Red::CRTTIArrayType*>(type)->innerType;
    auto inner_json = p_field.GetPtr<const JsonArray>();

    array_from_json(inner_json, inner_type, p_prop, p_object);
    return;
  }
}

template <typename T>
void array_from_json_fill(const JsonArray*& p_json, Red::DynArray<T>& p_array,
                          Red::CBaseRTTIType* p_inner_type) {
  for (uint32_t i = 0; i < p_json->get_size(); i++) {
    if constexpr (std::is_same_v<T, bool>) {
      p_array.PushBack(p_json->get_item_bool(i));
    } else if constexpr (std::is_same_v<T, int8_t> ||
                         std::is_same_v<T, int16_t> ||
                         std::is_same_v<T, int32_t> ||
                         std::is_same_v<T, int64_t>) {
      p_array.PushBack(p_json->get_item_int64(i));
    } else if constexpr (std::is_same_v<T, uint8_t> ||
                         std::is_same_v<T, uint16_t> ||
                         std::is_same_v<T, uint32_t> ||
                         std::is_same_v<T, uint64_t>) {
      p_array.PushBack(p_json->get_item_uint64(i));
    } else if constexpr (std::is_same_v<T, float> ||
                         std::is_same_v<T, double>) {
      p_array.PushBack(p_json->get_item_double(i));
    } else if constexpr (std::is_same_v<T, Red::CString>) {
      p_array.PushBack(p_json->get_item_string(i));
    } else if constexpr (std::is_same_v<T, Red::CName>) {
      p_array.EmplaceBack(p_json->get_item_string(i).c_str());
    } else if constexpr (std::is_same_v<T, Red::ResRef>) {
      Red::ResRef res_ref;

      res_ref.resource = Red::RaRef<Red::CResource>(
        Red::ResourcePath(p_json->get_item_string(i).c_str()));
      p_array.PushBack(res_ref);
    } else if constexpr (std::is_same_v<T, Red::TweakDBID>) {
      p_array.EmplaceBack(p_json->get_item_string(i).c_str());
    } else if constexpr (std::is_same_v<T, Red::Handle<Red::IScriptable>>) {
      auto item = p_json->get_item(i);

      if (!item->is_object() || item->is_null()) {
        p_array.EmplaceBack();
      } else {
        auto inner_object = Red::MakeScriptedHandle(p_inner_type->GetName());
        auto inner_json = item.GetPtr<const JsonObject>();

        object_from_json(inner_json, inner_object);
        p_array.PushBack(inner_object);
      }
    } else if constexpr (std::is_same_v<T, Red::WeakHandle<Red::IScriptable>>) {
      p_array.EmplaceBack();
    } /* else if (p_inner_type->GetType() == Red::ERTTIType::Array) {
      auto inner_type =
        reinterpret_cast<Red::CRTTIArrayType*>(p_inner_type)->innerType;
      auto inner_json = p_json->get_item(i).GetPtr<const JsonArray>();
      auto inner_array;

      p_array.PushBack(inner_array);
    }*/
  }
}

}  // namespace RedData::Json

RTTI_DEFINE_GLOBALS({
  RTTI_FUNCTION(RedData::Json::from_json, "RedData.Json.FromJson");
});
