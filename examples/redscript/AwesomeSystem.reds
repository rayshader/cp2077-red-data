// Copy file into r6\scripts\Awesome\
import Codeware.*
import RedData.Json.*

public class TestDto {
  let name: String;
  let version: Int64;
  let isEnabled: Bool;
  let data: ref<DataDto>;
  let prices: array<Float>;
}

public class DataDto {
  let buffer: array<Uint8>;
}

public class AwesomeSystem extends ScriptableSystem {
  private let m_callbackSystem: wref<CallbackSystem>;

  /// Lifecycle ///

  private func OnAttach() {
    this.m_callbackSystem = GameInstance.GetCallbackSystem();
    this.m_callbackSystem.RegisterCallback(n"Session/Ready", this, n"OnSessionReady");
  }

  private func OnDetach() {
    this.m_callbackSystem.UnregisterCallback(n"Session/Ready", this, n"OnSessionReady");
    this.m_callbackSystem = null;
  }

  /// Game events ///

  private cb func OnSessionReady(event: ref<GameSessionEvent>) {
    let isPreGame = event.IsPreGame();

    if !isPreGame {
      return;
    }
    FTLog(s"== RedData - Examples ==");
    let json = this.Example_Json();

    this.Example_Dto(json);
    FTLog(s"== RedData - Examples ==");
  }

  /// Examples ///

  public func Example_Json() -> ref<JsonObject> {
    FTLog("");
    FTLog("== Json ==");
    let json = new JsonObject();

    json.SetKeyString("name", "Awesome");
    json.SetKeyInt64("version", 1);
    json.SetKeyBool("isEnabled", true);
    json.SetKeyNull("data");
    let prices = new JsonArray();

    prices.AddItemDouble(19.99);
    prices.AddItemDouble(25.34);
    prices.AddItemDouble(1.30);
    prices.AddItemDouble(161.80);
    json.SetKey("prices", prices);
    let text = json.ToString();

    FTLog(text);
    json = ParseJson(text) as JsonObject;
    FTLog(s"name: \(json.GetKeyString("name"))");
    FTLog(s"version: \(json.GetKeyInt64("version"))");
    FTLog(s"isEnabled: \(json.GetKeyBool("isEnabled"))");
    FTLog(s"data: \(json.GetKey("data").IsNull())");
    prices = json.GetKey("prices") as JsonArray;
    FTLog(s"prices: \(prices.GetSize())");
    let i = 0u;

    while i < prices.GetSize() {
      FTLog(s"Price #\(i): €$ \(prices.GetItemDouble(i))");
      i += 1u;
    }
    return json;
  }

  public func Example_Dto(json: ref<JsonObject>) {
    FTLog("");
    FTLog("== FromJson ==");
    let test = FromJson(json, n"TestDto") as TestDto;

    FTLog(s"name: \(test.name)");
    FTLog(s"version: \(test.version)");
    FTLog(s"isEnabled: \(test.isEnabled)");
    FTLog(s"data: \(IsDefined(test.data))");
    let i = 0;

    for price in test.prices {
      FTLog(s"prices[\(i)]: €$ \(price)");
      i += 1;
    }
    FTLog("");
    FTLog("== ToJson ==");
    json = ToJson(test);
    FTLog(json.ToString());
  }

}