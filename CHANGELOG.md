# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Changed
- support patch 2.2.
- bump `simdjson` to 3.11.2 (was 3.10.1).

------------------------

## [0.5.0] - 2024-09-13
### Changed
- support patch 2.13.
- bump `simdjson` to 3.10.1 (was 3.9.4).

------------------------

## [0.4.3] - 2024-06-23
### Fixed
- crash when using `FromJson` with an empty type or when type is not found.

### Changed
- bump `simdjson` to 3.9.4 (was 3.9.1).

------------------------

## [0.4.2] - 2024-05-17
### Fixed
- issue when using `FromJson` to get a double from an integer would always
  return `0`.

------------------------

## [0.4.1] - 2024-05-15
### Fixed
- issue when using `ToJson` where array of `ref<T>` was converted to
  `[ [ {}, ...] ]` instead of `[ {}, ... ]`.

------------------------

## [0.4.0] - 2024-04-26
### Added
- optional indent argument when formatting with `ToString()`.

### Changed
- using `ToString()` will now format to minified Json by default.

------------------------

## [0.3.0] - 2024-04-22
### Added
- support for type `Uint64` with `JsonObject` and `JsonArray`.
- methods `FromJson` and `ToJson` to transform data two-way.

------------------------

## [0.2.0] - 2024-04-16
### Added
- declaration of module RedData.Json with all Json related features.

------------------------

## [0.1.0] - 2024-04-09
### Added
- parse/create/format Json data.

<!-- Table of releases -->
[Unreleased]: https://github.com/rayshader/cp2077-red-data/compare/v0.5.0...HEAD
[0.5.0]: https://github.com/rayshader/cp2077-red-data/compare/v0.4.3...v0.5.0
[0.4.3]: https://github.com/rayshader/cp2077-red-data/compare/v0.4.2...v0.4.3
[0.4.2]: https://github.com/rayshader/cp2077-red-data/compare/v0.4.1...v0.4.2
[0.4.1]: https://github.com/rayshader/cp2077-red-data/compare/v0.4.0...v0.4.1
[0.4.0]: https://github.com/rayshader/cp2077-red-data/compare/v0.3.0...v0.4.0
[0.3.0]: https://github.com/rayshader/cp2077-red-data/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/rayshader/cp2077-red-data/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/rayshader/cp2077-red-data/releases/tag/v0.1.0
