#ifndef REDDATA_JSONOBJECT_HPP
#define REDDATA_JSONOBJECT_HPP

#include <utility>
#include <vector>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.hpp"

namespace RedData::Json {

class JsonObject : public JsonVariant {
 public:
  JsonObject() = default;

  JsonObject(Red::Handle<Red::IScriptable> wrapper)
      : JsonVariant(std::move(wrapper)) {}

  Red::DynArray<Red::CString> GetKeys() const {
    Red::DynArray<Red::CString> keys;

    Red::CallVirtual(wrapper, "GetKeys", keys);
    return keys;
  }

  std::vector<JsonVariant> GetValues() const {
    Red::DynArray<Red::Handle<Red::IScriptable>> values;

    Red::CallVirtual(wrapper, "GetValues", values);
    std::vector<JsonVariant> items;

    for (const auto& value : values) {
      items.emplace_back(value);
    }
    return items;
  }

  bool HasKey(const Red::CString& key) const {
    bool result;

    Red::CallVirtual(wrapper, "HasKey", result, key);
    return result;
  }

  JsonVariant GetKey(const Red::CString& key) const {
    Red::Handle<Red::IScriptable> value;

    Red::CallVirtual(wrapper, "GetKey", value, key);
    return JsonVariant(value);
  }

  void SetKey(const Red::CString& key, const JsonVariant& value) {
    Red::CallVirtual(wrapper, "SetKey", key, value.GetHandle());
  }

  bool RemoveKey(const Red::CString& key) {
    bool result;

    Red::CallVirtual(wrapper, "RemoveKey", result, key);
    return result;
  }

  bool GetKeyBool(const Red::CString& key) const {
    bool value;

    Red::CallVirtual(wrapper, "GetKeyBool", value, key);
    return value;
  }

  int64_t GetKeyInt64(const Red::CString& key) const {
    int64_t value;

    Red::CallVirtual(wrapper, "GetKeyInt64", value, key);
    return value;
  }

  uint64_t GetKeyUint64(const Red::CString& key) const {
    uint64_t value;

    Red::CallVirtual(wrapper, "GetKeyUint64", value, key);
    return value;
  }

  double GetKeyDouble(const Red::CString& key) const {
    double value;

    Red::CallVirtual(wrapper, "GetKeyDouble", value, key);
    return value;
  }

  Red::CString GetKeyString(const Red::CString& key) const {
    Red::CString value;

    Red::CallVirtual(wrapper, "GetKeyString", value, key);
    return value;
  }

  void SetKeyNull(const Red::CString& key) {
    Red::CallVirtual(wrapper, "SetKeyNull", key);
  }

  void SetKeyBool(const Red::CString& key, bool value) {
    Red::CallVirtual(wrapper, "SetKeyBool", key, value);
  }

  void SetKeyInt64(const Red::CString& key, int64_t value) {
    Red::CallVirtual(wrapper, "SetKeyInt64", key, value);
  }

  void SetKeyUint64(const Red::CString& key, uint64_t value) {
    Red::CallVirtual(wrapper, "SetKeyUint64", key, value);
  }

  void SetKeyDouble(const Red::CString& key, double value) {
    Red::CallVirtual(wrapper, "SetKeyDouble", key, value);
  }

  void SetKeyString(const Red::CString& key, const Red::CString& value) {
    Red::CallVirtual(wrapper, "SetKeyString", key, value);
  }

  void Clear() { Red::CallVirtual(wrapper, "Clear"); }
};

}  // namespace RedData::Json

#endif  //REDDATA_JSONOBJECT_HPP
