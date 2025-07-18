# Red Data
![Cyberpunk 2077](https://img.shields.io/badge/Cyberpunk%202077-v2.3-blue)
![GitHub License](https://img.shields.io/github/license/rayshader/cp2077-red-data)
[![Donate](https://img.shields.io/badge/donate-buy%20me%20a%20coffee-yellow)](https://www.buymeacoffee.com/lpfreelance)

This plugin provides parsing/formatting for different data formats. It only 
supports Json for now. It can be used with Redscript and CET.

# Getting started

## Compatibility
- Cyberpunk 2077 v2.3
- [Redscript] 0.5.27+
- [Cyber Engine Tweaks] 1.36.0+

## Installation
1. Install requirements:
  - [RED4ext] v1.28.0+
2. Extract the [latest archive] into the Cyberpunk 2077 directory.

## API wrapper

This plugin can be used when writing a RED4ext plugin with RedLib. You can 
find a C++ API wrapper in [branch api].

## Usage

All Json features are defined in module `RedData.Json`. You need to import it 
with:
```swift
import RedData.Json.*
``` 

### Parse Json
> ParseJson(text: String) -> ref&lt;JsonVariant&gt;

e.g. with Json data:
```json
{
  "name": "RedData",
  "version": 1,
  "isEnabled": true,
  "pi": 3.14159265358979323846,
  "items": [2077, 13.37, true, "Cyberpunk"],
  "i18n": {
    "en-US": "Hello",
    "fr-FR": "Bonjour"
  }
}
```

You can parse Json content of a `String` like this:
```swift
// ...
let json = ParseJson("<json data from example above>");

if !IsDefined(json) {
  LogChannel(n"Error", s"Failed to parse Json.");
  return;
}
if !json.IsObject() {
  LogChannel(n"Error", s"Expect root of Json document to be an object.");
  return;
}
// ...
```

#### JsonVariant
> IsUndefined() -> Bool  
> IsNull() -> Bool
>
> IsBool() -> Bool  
> IsInt64() -> Bool  
> IsUint64() -> Bool  
> IsDouble() -> Bool  
> IsString() -> Bool
>
> IsArray() -> Bool  
> IsObject() -> Bool
> 
> ToString(opt indent: String) -> String

You can format Json data to a `String`. It will format output as minified Json 
by default. You can pretty format Json with spaces and/or tabulations using 
`indent` argument.
```swift
// ...
LogChannel(n"Info", s"Minified: \(json.ToString())");
LogChannel(n"Info", s"Pretty (two spaces): \(json.ToString("  "))");
LogChannel(n"Info", s"Pretty (tab): \(json.ToString("\t"))");
```

> [!NOTE]  
> Order of keys in a `JsonObject` is not preserved due to underlying 
> optimization.

> [!WARNING]  
> Using other characters than spaces and tabulations is not allowed. It will 
> fallback to minified Json instead.

#### JsonObject
> GetKeys() -> array&lt;String&gt;  
> GetValues() -> array&lt;ref&lt;JsonVariant&gt;&gt;
>
> HasKey(key: String) -> Bool  
> GetKey(key: String) -> ref&lt;JsonVariant&gt;  
> SetKey(key: String, value: ref&lt;JsonVariant&gt;) -> Void  
> RemoveKey(key: String) -> Bool
>
> GetKeyBool(key: String) -> Bool  
> GetKeyInt64(key: String) -> Int64  
> GetKeyUint64(key: String) -> Uint64  
> GetKeyDouble(key: String) -> Double  
> GetKeyString(key: String) -> String
>
> SetKeyNull(key: String) -> Void  
> SetKeyBool(key: String, value: Bool) -> Void  
> SetKeyInt64(key: String, value: Int64) -> Void  
> SetKeyUint64(key: String, value: Uint64) -> Void  
> SetKeyDouble(key: String, value: Double) -> Void  
> SetKeyString(key: String, value: String) -> Void
> 
> Clear() -> Void

Get values:
```swift
// ...
let obj = json as JsonObject;
let name = obj.GetKeyString("name");
let version = obj.GetKeyInt64("version");
let isEnabled = obj.GetKeyBool("isEnabled");
let pi = obj.GetKeyDouble("pi");
// Same as:
// let name = obj.GetKey("name").GetString();
// let version = obj.GetKey("version").GetInt64();
// let isEnabled = obj.GetKey("isEnabled").GetBool();
// let pi = obj.GetKey("pi").GetDouble();
```

Get a list of keys:
```swift
// ...
let keys = obj.GetKeys();

// keys == ["name", "version", "isEnabled", "pi", "items", "i18n"]
```

Get a list of values:
```swift
// ...
let values = obj.GetValues();

// values[0].GetString() == "RedData"
// values[1].GetInt64() == 1
// values[2].GetBool() == true
// values[3].GetDouble() == 3.14159265358979323846
// values[4] == [...]
// values[5] == {...}
```

Test whether a key is present:
```swift
// ...
let hasName = obj.HasKey("name");
let hasUnknown = obj.HasKey("unknown");

// hasName == true
// hasUnknown == false
```

#### JsonArray
> GetSize() -> Uint32  
> GetItem(index: Uint32) -> ref&lt;JsonVariant&gt;  
> SetItem(index: Uint32, value: ref&lt;JsonVariant&gt;) -> Void  
> RemoveItem(index: Uint32) -> Bool  
> AddItem(value: ref&lt;JsonVariant&gt;) -> Void  
> InsertItem(index: Uint32, value: ref&lt;JsonVariant&gt;) -> Void
> 
> GetItemBool(index: Uint32) -> Bool  
> GetItemInt64(index: Uint32) -> Int64  
> GetItemUint64(index: Uint32) -> Uint64  
> GetItemDouble(index: Uint32) -> Double  
> GetItemString(index: Uint32) -> String
>
> SetItemNull(index: Uint32) -> Void  
> SetItemBool(index: Uint32, value: Bool) -> Void  
> SetItemInt64(index: Uint32, value: Int64) -> Void  
> SetItemUint64(index: Uint32, value: Uint64) -> Void  
> SetItemDouble(index: Uint32, value: Double) -> Void  
> SetItemString(index: Uint32, value: String) -> Void
> 
> AddItemNull() -> Void  
> AddItemBool(value: Bool) -> Void  
> AddItemInt64(value: Int64) -> Void  
> AddItemUint64(value: Uint64) -> Void  
> AddItemDouble(value: Double) -> Void  
> AddItemString(value: String) -> Void
> 
> InsertItemNull(index: Uint32) -> Void  
> InsertItemBool(index: Uint32, value: Bool) -> Void  
> InsertItemInt64(index: Uint32, value: Int64) -> Void  
> InsertItemUint64(index: Uint32, value: Uint64) -> Void  
> InsertItemDouble(index: Uint32, value: Double) -> Void  
> InsertItemString(index: Uint32, value: String) -> Void
> 
> Clear() -> Void

Get items:
```swift
// ...
let items = obj.GetKey("items") as JsonArray;
let year = items.GetItemInt64(0u);
let elite = items.GetItemDouble(1u);
let theWay = items.GetItemBool(2u);
let title = items.GetItemString(3u);
// Same as:
// let year = items.GetItem(0u).GetInt64();
// let elite = items.GetItem(1u).GetDouble();
// let theWay = items.GetItem(2u).GetBool();
// let title = items.GetItem(3u).GetString();
```

Get the number of items:
```swift
let size: Uint32 = items.GetSize();
```

> Note: arrays are iterated from 1 to N when using Lua. In this case, you must 
> iterate from 0 to N - 1.

### Json to DTO
> FromJson(json: ref&lt;JsonObject&gt;, type: CName) -> ref&lt;IScriptable&gt;;

You can create a class from Json. It will match properties of the class with 
keys from Json data. The name of a property/key is case-sensitive.

```swift
public class MessageDto {
  let id: Uint64;
  let createdAt: Int32;
  let author: ref<UserDto>;
  let text: String;
}

public class UserDto {
  let id: Uint64;
  let firstName: String;
  let lastName: String;
  let permissions: array<String>;
}

let json = ParseJson("<Json data>") as JsonObject;
let message = FromJson(json, n"MessageDto") as MessageDto;
//                           ^
//                           | CName of the class to format Json to.

LogChannel(n"Info", s"text: \"\(message.text)\"");
```

This feature supports the following types:
- `Bool`
- `Int8`, `Int16`, `Int32`, `Int64`
- `Uint8`, `Uint16`, `Uint32`, `Uint64`
- `Float`, `Double`
- `String`, `CName`, `ResRef`, `TweakDBID`
- `ref<T>`, `array<T>`

When property is:
- a weak reference: the value is always set to `null`.
- a strong reference: the value is set with a new instance built from the Json 
data, or it fallbacks to `null`.
- an array: the value is set with an array built from the 
Json data.

> [!NOTE]  
> Type of array can be any of the supported types above, but it does not 
> support arrays within arrays.

### DTO to Json
> ToJson(object: ref&lt;IScriptable&gt;) -> ref&lt;JsonObject&gt;;

You can create Json data from a class. It will create a `JsonObject` based on 
properties of the object.

```swift
// ...
let message = new MessageDto();

message.id = 42;
message.createdAt = 1337;
message.author = null;
message.text = "Hello world!";
let json = ToJson(message);

LogChannel(n"Info", s"json: \(json.ToString("  "))");
// It should log:
// {
//   "id": 42,
//   "createdAt": 1337,
//   "author": null,
//   "text": "Hello world!"
// }
```

This feature supports the following types:
- `Bool`
- `Int8`, `Int16`, `Int32`, `Int64`
- `Uint8`, `Uint16`, `Uint32`, `Uint64`
- `Float`, `Double`
- `String`, `CName`
- `ref<T>`, `array<T>`

`ResRef` and `TweakDBID` are not supported because they cannot be transformed 
back to a `String`.

> [!NOTE]  
> Type of an array can be any of the supported types above, but it does not 
> support arrays within arrays.

### Create Json data
You can create JsonObject/JsonArray.

```swift
// ...
let json = new JsonObject();

json.SetKeyString("name", "RedData");
json.SetKeyBool("isEnabled", true);
json.SetKeyDouble("version", 2.12);
let items = new JsonArray();

items.AddItemNull();
items.AddItemBool(true);
items.AddItemInt64(2077);
items.AddItemDouble(13.37);
items.AddItemString("Welcome to Night City!");
json.SetKey("items", items);
let text = json.ToString("\t");

LogChannel(n"Info", s"Json:");
LogChannel(n"Info", text);
```

# Development
Contributions are welcome, feel free to fill an issue or a PR.

## Usage
1. Install requirements:
  - CMake v3.27+
  - Visual Studio Community 2022+
  - [red-cli] v0.4.0+
2. Configure project with:
```shell
cmake -G "Visual Studio 17 2022" -A x64 -S . -B build
```

3. Build in debug mode:
```shell
cmake --build build --target RedData --config Debug
```

It will execute `red-cli install` for you using a CMake custom command.

## Tests
1. Run game.
2. Open CET, show Game Log popup.
3. Output should show tests result.

## Release
1. Build in release mode:

```shell
cmake --build build --target RedData --config Release
```

It will execute `red-cli pack` for you using a CMake custom command. You should
find an archive `RedData-X.Y.Z.zip` in the root directory, ready to release.

<!-- Table of links -->
[RED4ext]: https://github.com/WopsS/RED4ext
[Redscript]: https://github.com/jac3km4/redscript
[Cyber Engine Tweaks]: https://github.com/maximegmd/CyberEngineTweaks
[latest archive]: https://github.com/rayshader/cp2077-red-data/releases/latest
[Codeware]: https://github.com/psiberx/cp2077-codeware/wiki#lifecycle
[examples/]: https://github.com/rayshader/cp2077-red-data/tree/master/examples
[branch api]: https://github.com/rayshader/cp2077-red-data/tree/api
[red-cli]: https://github.com/rayshader/cp2077-red-cli/releases/latest