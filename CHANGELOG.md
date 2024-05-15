# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
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
[Unreleased]: https://github.com/rayshader/cp2077-red-data/compare/v0.4.0...HEAD
[0.4.0]: https://github.com/rayshader/cp2077-red-data/compare/v0.3.0...v0.4.0
[0.3.0]: https://github.com/rayshader/cp2077-red-data/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/rayshader/cp2077-red-data/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/rayshader/cp2077-red-data/releases/tag/v0.1.0
