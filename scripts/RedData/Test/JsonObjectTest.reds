import RedData.Json.*

public class JsonObjectTest extends JsonBaseTest {

  public func Create() {
    this.m_modName = "RedData";
    this.m_name = "JsonObject";
  }

  private cb func Test_Constructor() {
    let object = new JsonObject();

    this.ExpectBool("Constructor is object", object.IsObject(), true);
    this.ExpectBool("Constructor $.none is null", IsDefined(object.GetKey("none")), false);
  }

  /*
  private cb func Test_GetKeys() {
    let object = new JsonObject();

    //
  }
  */

  private cb func Test_ToString() {
    let json = new JsonObject();

    json.SetKeyString("message", "Welcome to Night City!");
    json.SetKeyDouble("version", 2.11);
    json.SetKeyInt64("code", 1337);
    json.SetKeyBool("test", true);
    json.SetKeyNull("empty");
    let array = new JsonArray();

    array.AddItemString("Hello");
    array.AddItemInt64(42);
    array.AddItemDouble(3.14159);
    array.AddItemNull();
    json.SetKey("items", array);
    let actual = json.ToString();
    // Follow hash order of 'std::unordered_map'.
    let expect = "{\n" +
                 "  \"code\": 1337,\n" +
                 "  \"message\": \"Welcome to Night City!\",\n" +
                 "  \"items\": [\n" +
                 "    \"Hello\",\n" +
                 "    42,\n" +
                 "    3.14159,\n" +
                 "    null\n" +
                 "  ],\n" +
                 "  \"version\": 2.11,\n" +
                 "  \"test\": true,\n" +
                 "  \"empty\": null\n" +
                 "}";

    this.ExpectUnicodeString("ToString", actual, expect);
  }

}
