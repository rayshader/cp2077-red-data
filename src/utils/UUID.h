#pragma once

namespace RedData {

struct UUID {
    uuids::uuid value;

    [[nodiscard]] static UUID generate();
    [[nodiscard]] static bool equals(const UUID& p_a, const UUID& p_b);
    [[nodiscard]] static bool is_valid(const UUID& p_uuid);
    [[nodiscard]] static UUID from_string(const Red::CString& p_value);
    [[nodiscard]] static Red::CString to_string(const UUID& p_uuid);

    RTTI_IMPL_TYPEINFO(RedData::UUID);
    RTTI_IMPL_ALLOCATOR();
};

}

RTTI_DEFINE_CLASS(RedData::UUID, {
  RTTI_ALIAS("RedData.UUID");

  RTTI_METHOD(generate, "Generate");
  RTTI_METHOD(equals, "Equals");
  RTTI_METHOD(is_valid, "IsValid");
  RTTI_METHOD(from_string, "FromString");
  RTTI_METHOD(to_string, "ToString");
});
