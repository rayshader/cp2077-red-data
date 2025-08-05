module RedData.Json

public native func ParseJson(text: String) -> ref<JsonVariant>;
public native func FromJson(json: ref<JsonObject>, type: CName) -> ref<IScriptable>;
public native func ToJson(object: ref<IScriptable>) -> ref<JsonObject>;