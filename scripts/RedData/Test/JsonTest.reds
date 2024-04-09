public class JsonTest extends JsonBaseTest {
  private let m_json: String = "{\"name\":\"FileSystemTest\",\"version\":1,\"isJson\":true,\"delta\":0.016,\"pangrams\":{\"Arabic\":\"صِف خَلقَ خَودِ كَمِثلِ الشَمسِ إِذ بَزَغَت — يَحظى الضَجيعُ بِها نَجلاءَ مِعطارِ (A poem by Al Farāhīdi)\",\"Hindi\":\"ऋषियों को सताने वाले दुष्ट राक्षसों के राजा रावण का सर्वनाश करने वाले विष्णुवतार भगवान श्रीराम, अयोध्या के महाराज दशरथ के बड़े सपुत्र थे।\",\"Japanese\":\"いろはにほへと ちりぬるを わかよたれそ つねならむ うゐのおくやま けふこえて あさきゆめみし ゑひもせす（ん）\",\"Latin\":\"Sic fugiens, dux, zelotypos, quam Karus haberis.\"},\"random\":[true,42,13.37,\"Weird\",{\"object\":null},[\"array\"]]}";

  public func Init() {
    this.m_modName = "RedData";
    this.m_name = "Json";
  }

  private cb func Test_ParseJson_Invalid() {
    let json = ParseJson("{key: value}");

    this.ExpectBool("Json is invalid", IsDefined(json), false);
  }

  private cb func Test_ParseJson_Valid() {
    let json = ParseJson(this.m_json) as JsonObject;

    this.ExpectBool("Json is valid", IsDefined(json), true);
    this.ExpectJsonKeyString("$.name == 'FileSystemTest'", json, "name", "FileSystemTest");
    this.ExpectJsonKeyInt64("$.version == 1", json, "version", 1);
    this.ExpectJsonKeyBool("$.isJson == true", json, "isJson", true);
    this.ExpectJsonKeyDouble("$.delta == 0.016", json, "delta", 0.016);
    let pangrams = json.GetKey("pangrams") as JsonObject;
    let pass = this.ExpectBool("$.pangrams === {...}", pangrams.IsObject(), true);

    if !pass {
      LogChannel(n"Error", "$.pangrams /!\\ invalid Json format /!\\");
      return;
    }
    this.ExpectJsonKeyUnicodeString("$.pangrams.Arabic", pangrams, "Arabic", "صِف خَلقَ خَودِ كَمِثلِ الشَمسِ إِذ بَزَغَت — يَحظى الضَجيعُ بِها نَجلاءَ مِعطارِ (A poem by Al Farāhīdi)");
    this.ExpectJsonKeyUnicodeString("$.pangrams.Hindi", pangrams, "Hindi", "ऋषियों को सताने वाले दुष्ट राक्षसों के राजा रावण का सर्वनाश करने वाले विष्णुवतार भगवान श्रीराम, अयोध्या के महाराज दशरथ के बड़े सपुत्र थे।");
    this.ExpectJsonKeyUnicodeString("$.pangrams.Japanese", pangrams, "Japanese", "いろはにほへと ちりぬるを わかよたれそ つねならむ うゐのおくやま けふこえて あさきゆめみし ゑひもせす（ん）");
    this.ExpectJsonKeyUnicodeString("£.pangrams.Latin", pangrams, "Latin", "Sic fugiens, dux, zelotypos, quam Karus haberis.");
    let random = json.GetKey("random") as JsonArray;

    pass = this.ExpectBool("$.random === [...]", random.IsArray(), true);
    if !pass {
      LogChannel(n"Error", "$.random /!\\ invalid Json format /!\\");
      return;
    }
    this.ExpectBool("$.random[0]", random.GetItemBool(0u), true);
    this.ExpectInt64("$.random[1]", random.GetItemInt64(1u), 42l);
    this.ExpectDouble("$.random[2]", random.GetItemDouble(2u), 13.37);
    this.ExpectString("$.random[3]", random.GetItemString(3u), "Weird");
    let obj = random.GetItem(4u) as JsonObject;

    pass = this.ExpectBool("$.random[4] === {...}", obj.IsObject(), true);
    if !pass {
      LogChannel(n"Error", "$.random[4] /!\\ invalid Json format /!\\");
      return;
    }
    this.ExpectJsonKeyNull("$.random[4].object", obj, "object");
    let array = random.GetItem(5u) as JsonArray;

    pass = this.ExpectBool("$.random[5] === [...]", array.IsArray(), true);
    if !pass {
      LogChannel(n"Error", "$.random[5] /!\\ invalid Json format /!\\");
      return;
    }
    this.ExpectString("$.random[5][0]", array.GetItemString(0u), "array");
  }

}
