# Red Data Api
![Cyberpunk 2077](https://img.shields.io/badge/Cyberpunk%202077-v2.12-blue)
![GitHub License](https://img.shields.io/github/license/rayshader/cp2077-red-filesystem)
[![Donate](https://img.shields.io/badge/donate-buy%20me%20a%20coffee-yellow)](https://www.buymeacoffee.com/lpfreelance)

This header-only library provides an API wrapper for [RedData] plugin.

# Getting started

## Compatibility
- [RedData] v0.2.0

## Requirements
- [RED4ext.SDK]
- [RedLib]

## Usage

API is defined in namespace `RedData`.

You can test whether plugin is installed/detected in-game using:
```cpp
bool isDetected = RedData::IsDetected();
```

This API is a mirror of redscript declarations. You can also directly test 
whether an instance is defined using `operator bool()` such as:
```cpp
RedData::Json::JsonVariant json;

if (!json) {
    // Handle is null.
    return;
}
// Use it...
```

You can get raw handle with:
```cpp
RedData::Json::JsonVariant json;

Red::Handle<Red::IScriptable> handle = json;
// or
handle = json.GetHandle();
```

# Development
Contributions are welcome, feel free to fill an issue or a PR.

<!-- Table of links -->
[RED4ext.SDK]: https://github.com/WopsS/RED4ext.SDK
[RedLib]: https://github.com/psiberx/cp2077-red-lib
[RedData]: https://github.com/rayshader/cp2077-red-data
