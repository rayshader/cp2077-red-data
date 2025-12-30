#include "UUID.h"

namespace RedData {

UUID UUID::generate() {
    static uuids::uuid_system_generator generator{};
    return {.value = generator()};
}

bool UUID::equals(const UUID& p_a, const UUID& p_b) {
    return p_a.value == p_b.value;
}

bool UUID::is_valid(const UUID& p_uuid) {
    return !p_uuid.value.is_nil();
}

UUID UUID::from_string(const Red::CString& p_value) {
    const auto uuid = uuids::uuid::from_string(p_value.c_str());
    if (!uuid) {
        return {};
    }

    return {.value = uuid.value()};
}

Red::CString UUID::to_string(const UUID& p_uuid) {
    return uuids::to_string(p_uuid.value);
}

}
