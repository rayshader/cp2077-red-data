// Copy file into r6\scripts\Awesome\
import Codeware.*

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
    LogChannel(n"Info", s"== RedData - Examples ==");
    this.Example_Json();
    LogChannel(n"Info", s"== RedData - Examples ==");
  }

  /// Examples ///

  public func Example_Json() {
    LogChannel(n"Info", "");
    LogChannel(n"Info", "== Json ==");
    let json = new JsonObject();

    json.SetKeyString("name", "Awesome");
    json.SetKeyInt64("version", 1);
    json.SetKeyBool("isEnabled", true);
    json.SetKeyNull("data");
    let text = json.ToString();

    LogChannel(n"Info", text);
    json = ParseJson(text) as JsonObject;
    LogChannel(n"Info", s"name: \(json.GetKeyString("name"))");
    LogChannel(n"Info", s"version: \(json.GetKeyInt64("version"))");
    LogChannel(n"Info", s"isEnabled: \(json.GetKeyBool("isEnabled"))");
    LogChannel(n"Info", s"data: \(json.GetKey("data").IsNull())");
  }

}