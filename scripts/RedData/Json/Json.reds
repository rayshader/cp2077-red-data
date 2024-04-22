public static native func ParseJson(text: String) -> ref<JsonVariant>;
public static native func FromJson(json: ref<JsonObject>, type: CName) -> ref<IScriptable>;
public static native func ToJson(object: ref<IScriptable>) -> ref<JsonObject>;