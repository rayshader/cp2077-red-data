import Codeware.*

public class RedDataTest extends ScriptableEnv {
  private let m_runner: ref<RedTest>;

  /// Lifecycle ///

  private cb func OnLoad() {
    this.m_runner = new RedTest();
    this.m_runner.Setup("RedData", [
      new JsonArrayTest(),
      new JsonObjectTest(),
      new JsonTest() as BaseTest
    ]);
  }

}

public static func GetRedDataTest() -> ref<RedDataTest> {
  return ScriptableEnv.Get(n"RedDataTest") as RedDataTest;
}
