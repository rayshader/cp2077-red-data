cmake_minimum_required(VERSION 3.27)
project(RedData VERSION 0.5.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

configure_file(src/Config.h.in Config/Config.h)

set(INC_FILES
        src/json/Json.h
        src/json/FromJson.h
        src/json/JsonType.h
        src/json/JsonVariant.h
        src/json/JsonNull.h
        src/json/JsonBool.h
        src/json/JsonNumber.h
        src/json/JsonString.h
        src/json/JsonArray.h
        src/json/JsonObject.h
        src/json/JsonFactory.h
        src/json/ToJson.h
)

set(SRC_FILES
        src/main.cpp

        src/json/Json.cpp
        src/json/FromJson.cpp
        src/json/JsonVariant.cpp
        src/json/JsonNull.cpp
        src/json/JsonBool.cpp
        src/json/JsonNumber.cpp
        src/json/JsonString.cpp
        src/json/JsonArray.cpp
        src/json/JsonObject.cpp
        src/json/ToJson.cpp
)

source_group(include FILES INC_FILES)
source_group(source FILES SRC_FILES)

add_library(RedData SHARED
        ${INC_FILES}
        ${SRC_FILES}
)

target_include_directories(RedData PRIVATE src/)
target_include_directories(RedData PRIVATE src/json/)

# Include configured files
target_include_directories(RedData PUBLIC "${PROJECT_BINARY_DIR}/Config")

# Exclude unused Windows headers
add_compile_definitions(WIN32_LEAN_AND_MEAN)

## Library RED4ext.SDK
option(RED4EXT_HEADER_ONLY "" ON)
add_subdirectory(deps/RED4ext.SDK)
set_target_properties(RED4ext.SDK PROPERTIES FOLDER "Dependencies")
mark_as_advanced(RED4EXT_BUILD_EXAMPLES RED4EXT_HEADER_ONLY)
##

## Library RedLib
add_compile_definitions(NOMINMAX)
add_subdirectory(deps/RedLib)
set_target_properties(RedLib PROPERTIES FOLDER "Dependencies")
##

## Library simdjson
include(FetchContent)

FetchContent_Declare(
        simdjson
        GIT_REPOSITORY https://github.com/simdjson/simdjson.git
        GIT_TAG  tags/v3.11.2
        GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(simdjson)
##

target_link_libraries(RedData PRIVATE
        RED4ext::SDK
        RedLib
        simdjson
)

## Debug mode: install scripts (+ tests) and plugin in game folder.
## Release mode: create archive with bundled scripts and plugin.
add_custom_command(
        TARGET RedData
        POST_BUILD
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "$<$<CONFIG:Debug>:Install scripts with red-cli>" "$<$<CONFIG:Release>:Build archive with red-cli>"
        COMMAND "$<$<CONFIG:Debug>:red-cli;install>" "$<$<CONFIG:Release>:red-cli;pack>"
        COMMAND_EXPAND_LISTS
)