-- Copy file into bin\x64\plugins\cyber_engine_tweaks\mods\AwesomeExample\

local function ExampleJson()
  print()
  print("== Json ==")
  local json = JsonObject.new()

  json:SetKeyString("name", "Awesome")
  json:SetKeyInt64("version", 1)
  json:SetKeyBool("isEnabled", true)
  json:SetKeyNull("data")
  print(json:ToString())
end

registerForEvent('onInit', function()
  print("== RedData - Examples ==")
  ExampleJson()
  print("== RedData - Examples ==")
end)