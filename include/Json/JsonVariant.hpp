#ifndef REDDATA_JSONVARIANT_HPP
#define REDDATA_JSONVARIANT_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>
#include <utility>

namespace RedData::Json {

class JsonVariant {
 protected:
  Red::Handle<Red::IScriptable> wrapper;

 public:
  JsonVariant() = default;

  JsonVariant(Red::Handle<Red::IScriptable> wrapper)
      : wrapper(std::move(wrapper)) {}

  explicit operator bool() const noexcept { return wrapper.operator bool(); }

  operator Red::Handle<Red::IScriptable>() const noexcept { return wrapper; }

  Red::Handle<Red::IScriptable> GetHandle() const { return wrapper; }

  bool IsUndefined() const {
    bool result;

    Red::CallVirtual(wrapper, "IsUndefined", result);
    return result;
  }

  bool IsNull() const {
    bool result;

    Red::CallVirtual(wrapper, "IsNull", result);
    return result;
  }

  bool IsBool() const {
    bool result;

    Red::CallVirtual(wrapper, "IsBool", result);
    return result;
  }

  bool IsInt64() const {
    bool result;

    Red::CallVirtual(wrapper, "IsInt64", result);
    return result;
  }

  bool IsUint64() const {
    bool result;

    Red::CallVirtual(wrapper, "IsUint64", result);
    return result;
  }

  bool IsDouble() const {
    bool result;

    Red::CallVirtual(wrapper, "IsDouble", result);
    return result;
  }

  bool IsString() const {
    bool result;

    Red::CallVirtual(wrapper, "IsString", result);
    return result;
  }

  bool IsArray() const {
    bool result;

    Red::CallVirtual(wrapper, "IsArray", result);
    return result;
  }

  bool IsObject() const {
    bool result;

    Red::CallVirtual(wrapper, "IsObject", result);
    return result;
  }

  Red::CString ToString(const Red::CString& indent = "") const {
    Red::CString str;

    Red::CallVirtual(wrapper, "ToString", str, indent);
    return str;
  }
};

}  // namespace RedData::Json

#endif  //REDDATA_JSONVARIANT_HPP
