#ifndef REDDATA_JSONARRAY_HPP
#define REDDATA_JSONARRAY_HPP

#include <utility>
#include <vector>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "JsonVariant.hpp"

namespace RedData::Json {

class JsonArray : public JsonVariant {
 public:
  JsonArray() = default;

  JsonArray(Red::Handle<Red::IScriptable> wrapper)
      : JsonVariant(std::move(wrapper)) {}

  uint32_t GetSize() const {
    uint32_t size;

    Red::CallVirtual(wrapper, "GetSize");
    return size;
  }

  JsonVariant GetItem(uint32_t index) const {
    Red::Handle<Red::IScriptable> handle;

    Red::CallVirtual(wrapper, "GetItem", handle, index);
    return JsonVariant(handle);
  }

  void SetItem(uint32_t index, const JsonVariant& value) const {
    Red::CallVirtual(wrapper, "SetItem", index, value.GetHandle());
  }

  bool RemoveItem(uint32_t index) const {
    bool result;

    Red::CallVirtual(wrapper, "RemoveItem", result, index);
    return result;
  }

  void AddItem(const JsonVariant& value) const {
    Red::CallVirtual(wrapper, "AddItem", value.GetHandle());
  }

  void InsertItem(uint32_t index, const JsonVariant& value) const {
    Red::CallVirtual(wrapper, "InsertItem", index, value.GetHandle());
  }

  bool GetItemBool(uint32_t index) const {
    bool value;

    Red::CallVirtual(wrapper, "GetItemBool", value, index);
    return value;
  }

  int64_t GetItemInt64(uint32_t index) const {
    int64_t value;

    Red::CallVirtual(wrapper, "GetItemInt64", value, index);
    return value;
  }

  uint64_t GetItemUint64(uint32_t index) const {
    uint64_t value;

    Red::CallVirtual(wrapper, "GetItemUint64", value, index);
    return value;
  }

  double GetItemDouble(uint32_t index) const {
    double value;

    Red::CallVirtual(wrapper, "GetItemDouble", value, index);
    return value;
  }

  Red::CString GetItemString(uint32_t index) const {
    Red::CString value;

    Red::CallVirtual(wrapper, "GetItemString", value, index);
    return value;
  }

  void SetItemNull(uint32_t index) const {
    Red::CallVirtual(wrapper, "SetItemNull", index);
  }

  void SetItemBool(uint32_t index, bool value) const {
    Red::CallVirtual(wrapper, "SetItemBool", index, value);
  }

  void SetItemInt64(uint32_t index, int64_t value) const {
    Red::CallVirtual(wrapper, "SetItemInt64", index, value);
  }

  void SetItemUint64(uint32_t index, uint64_t value) const {
    Red::CallVirtual(wrapper, "SetItemUint64", index, value);
  }

  void SetItemDouble(uint32_t index, double value) const {
    Red::CallVirtual(wrapper, "SetItemDouble", index, value);
  }

  void SetItemString(uint32_t index, const Red::CString& value) const {
    Red::CallVirtual(wrapper, "SetItemString", index, value);
  }

  void AddItemNull() const { Red::CallVirtual(wrapper, "AddItemNull"); }

  void AddItemBool(bool value) const {
    Red::CallVirtual(wrapper, "AddItemBool", value);
  }

  void AddItemInt64(int64_t value) const {
    Red::CallVirtual(wrapper, "AddItemInt64", value);
  }

  void AddItemUint64(uint64_t value) const {
    Red::CallVirtual(wrapper, "AddItemUint64", value);
  }

  void AddItemDouble(double value) const {
    Red::CallVirtual(wrapper, "AddItemDouble", value);
  }

  void AddItemString(const Red::CString& value) const {
    Red::CallVirtual(wrapper, "AddItemString", value);
  }

  void InsertItemNull(uint32_t index) const {
    Red::CallVirtual(wrapper, "InsertItemNull", index);
  }

  void InsertItemBool(uint32_t index, bool value) const {
    Red::CallVirtual(wrapper, "InsertItemBool", index, value);
  }

  void InsertItemInt64(uint32_t index, int64_t value) const {
    Red::CallVirtual(wrapper, "InsertItemInt64", index, value);
  }

  void InsertItemUint64(uint32_t index, uint64_t value) const {
    Red::CallVirtual(wrapper, "InsertItemUint64", index, value);
  }

  void InsertItemDouble(uint32_t index, double value) const {
    Red::CallVirtual(wrapper, "InsertItemDouble", index, value);
  }

  void InsertItemString(uint32_t index, const Red::CString& value) const {
    Red::CallVirtual(wrapper, "InsertItemString", index, value);
  }

  void Clear() { Red::CallVirtual(wrapper, "Clear"); }
};

}  // namespace RedData::Json

#endif  //REDDATA_JSONARRAY_HPP
