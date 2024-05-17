import RedData.Json.*

public class TypesDto {
  let pBool: Bool;

  let pInt8: Int8;
  let pInt16: Int16;
  let pInt32: Int32;
  let pInt64: Int64;

  let pUint8: Uint8;
  let pUint16: Uint16;
  let pUint32: Uint32;
  let pUint64: Uint64;

  let pFloat: Float;
  let pFloatInt: Float;
  let pDouble: Double;
  let pDoubleInt: Double;

  let pString: String;
  let pCName: CName;
  let pResRef: ResRef;
  let pTweakDBID: TweakDBID;
}

public class SessionDto {
  let id: Uint64;
  let createdAt: Int32;
  let user: ref<UserDto>;
  let empty: ref<UserDto>;
  let friends: array<ref<FriendDto>>;
}

public class FriendDto {
  let id: Uint64;
  let username: String;

  public static func Create(id: Uint64, username: String) -> ref<FriendDto> {
    let self = new FriendDto();

    self.id = id;
    self.username = username;
    return self;
  }
}

public class UserDto {
  let id: Uint64;
  let username: String;
  let isAdmin: Bool;
  let words: array<String>;
  let i8: array<Int8>;
  let names: array<CName>;
}

public class JsonTest extends JsonBaseTest {
  private let m_json: String = "{\"name\":\"FileSystemTest\",\"version\":1,\"isJson\":true,\"delta\":0.016,\"pangrams\":{\"Arabic\":\"صِف خَلقَ خَودِ كَمِثلِ الشَمسِ إِذ بَزَغَت — يَحظى الضَجيعُ بِها نَجلاءَ مِعطارِ (A poem by Al Farāhīdi)\",\"Hindi\":\"ऋषियों को सताने वाले दुष्ट राक्षसों के राजा रावण का सर्वनाश करने वाले विष्णुवतार भगवान श्रीराम, अयोध्या के महाराज दशरथ के बड़े सपुत्र थे।\",\"Japanese\":\"いろはにほへと ちりぬるを わかよたれそ つねならむ うゐのおくやま けふこえて あさきゆめみし ゑひもせす（ん）\",\"Latin\":\"Sic fugiens, dux, zelotypos, quam Karus haberis.\"},\"random\":[true,42,13.37,\"Weird\",{\"object\":null},[\"array\"]]}";
  private let m_jsonDto: String;
  private let m_jsonNestedDto: String;

  public func Create() {
    this.m_modName = "RedData";
    this.m_name = "Json";
  }

  public func Setup() {
    this.m_jsonDto = "{";
    this.m_jsonDto +=   "\"pBool\": true,";
    this.m_jsonDto +=   "\"pInt8\": 127,\"pInt16\": 32767,\"pInt32\": 2147483647,\"pInt64\": 9223372036854775807,";
    this.m_jsonDto +=   "\"pUint8\": 255,\"pUint16\": 65535,\"pUint32\": 4294967295,\"pUint64\": 18446744073709551615,";
    this.m_jsonDto +=   "\"pFloat\": 3.141592, \"pFloatInt\": 1,\"pDouble\": 3.141592653589793, \"pDoubleInt\": 42,";
    this.m_jsonDto +=   "\"pString\": \"Hello world!\",\"pCName\": \"VehicleObject\",\"pResRef\": \"base\\\\anim_cooked.cookedanims\",\"pTweakDBID\": \"Items.RequiredItemStats\"";
    this.m_jsonDto += "}";

    this.m_jsonNestedDto = "{";
    this.m_jsonNestedDto +=   "\"id\": 1337,";
    this.m_jsonNestedDto +=   "\"createdAt\": 1713646202,";
    this.m_jsonNestedDto +=   "\"user\": {";
    this.m_jsonNestedDto +=     "\"id\": 42,";
    this.m_jsonNestedDto +=     "\"username\": \"NightCity\",";
    this.m_jsonNestedDto +=     "\"isAdmin\": true,";
    this.m_jsonNestedDto +=     "\"words\": [\"Hello\",\"world\",\"!\"],";
    this.m_jsonNestedDto +=     "\"i8\": [-128,-1,0,1,127],";
    this.m_jsonNestedDto +=     "\"names\": [\"VehicleObject\",\"PlayerPuppet\",\"WeaponObject\"]";
    this.m_jsonNestedDto +=   "},";
    this.m_jsonNestedDto +=   "\"friends\": [";
    this.m_jsonNestedDto +=   "  {\"id\": 1, \"username\": \"Welles\"},";
    this.m_jsonNestedDto +=   "  {\"id\": 2, \"username\": \"Silverhand\"},";
    this.m_jsonNestedDto +=   "  {\"id\": 3, \"username\": \"Takemura\"},";
    this.m_jsonNestedDto +=   "  {\"id\": 4, \"username\": \"Vector\"}";
    this.m_jsonNestedDto +=   "]";
    this.m_jsonNestedDto += "}";
  }

  private cb func Test_ToString_DefaultIsMinified() {
    let json = new JsonObject();

    json.SetKeyString("message", "Welcome to Night City!");
    json.SetKeyDouble("version", 2.12);
    json.SetKeyInt64("code", 9223372036854775807l);
    json.SetKeyUint64("long_code", 18446744073709551615ul);
    json.SetKeyBool("test", true);
    json.SetKeyNull("empty");
    let array = new JsonArray();

    array.AddItemString("Hello");
    array.AddItemInt64(42);
    array.AddItemUint64(1337ul);
    array.AddItemDouble(3.14159);
    array.AddItemNull();
    json.SetKey("items", array);
    let actual = json.ToString();
    // Follow hash order of 'std::unordered_map'.
    let expect = "{" +
                   "\"code\":9223372036854775807," +
                   "\"message\":\"Welcome to Night City!\"," +
                   "\"items\":[" +
                     "\"Hello\"," +
                     "42," +
                     "1337," +
                     "3.14159," +
                     "null" +
                   "]," +
                   "\"version\":2.12," +
                   "\"long_code\":18446744073709551615," +
                   "\"test\":true," +
                   "\"empty\":null" +
                 "}";

    this.ExpectUnicodeString("ToString() is minified", actual, expect);
  }

  private cb func Test_ToString_Pretty() {
    let json = new JsonObject();

    json.SetKeyString("message", "Welcome to Night City!");
    json.SetKeyDouble("version", 2.12);
    json.SetKeyInt64("code", 9223372036854775807l);
    json.SetKeyUint64("long_code", 18446744073709551615ul);
    json.SetKeyBool("test", true);
    json.SetKeyNull("empty");
    let array = new JsonArray();

    array.AddItemString("Hello");
    array.AddItemInt64(42);
    array.AddItemUint64(1337ul);
    array.AddItemDouble(3.14159);
    array.AddItemNull();
    json.SetKey("items", array);
    let actual = json.ToString("  ");
    // Follow hash order of 'std::unordered_map'.
    let expect = "{\n" +
                 "  \"code\": 9223372036854775807,\n" +
                 "  \"message\": \"Welcome to Night City!\",\n" +
                 "  \"items\": [\n" +
                 "    \"Hello\",\n" +
                 "    42,\n" +
                 "    1337,\n" +
                 "    3.14159,\n" +
                 "    null\n" +
                 "  ],\n" +
                 "  \"version\": 2.12,\n" +
                 "  \"long_code\": 18446744073709551615,\n" +
                 "  \"test\": true,\n" +
                 "  \"empty\": null\n" +
                 "}";

    this.ExpectUnicodeString("ToString(\"  \") is pretty formatted", actual, expect);
  }

  private cb func Test_ToString_IllegalIndent() {
    let json = new JsonObject();

    json.SetKeyString("message", "Welcome to Night City!");
    json.SetKeyDouble("version", 2.12);
    json.SetKeyInt64("code", 9223372036854775807l);
    json.SetKeyUint64("long_code", 18446744073709551615ul);
    json.SetKeyBool("test", true);
    json.SetKeyNull("empty");
    let array = new JsonArray();

    array.AddItemString("Hello");
    array.AddItemInt64(42);
    array.AddItemUint64(1337ul);
    array.AddItemDouble(3.14159);
    array.AddItemNull();
    json.SetKey("items", array);
    let actual = json.ToString("abc_-.012");
    // Follow hash order of 'std::unordered_map'.
    let expect = "{" +
                   "\"code\":9223372036854775807," +
                   "\"message\":\"Welcome to Night City!\"," +
                   "\"items\":[" +
                     "\"Hello\"," +
                     "42," +
                     "1337," +
                     "3.14159," +
                     "null" +
                   "]," +
                   "\"version\":2.12," +
                   "\"long_code\":18446744073709551615," +
                   "\"test\":true," +
                   "\"empty\":null" +
                 "}";

    this.ExpectUnicodeString("ToString(\"abc_-.012\") illegal indent fallback to default", actual, expect);
  }

  private cb func Test_ParseJson_Invalid() {
    let json = ParseJson("{key: value}");

    this.ExpectBool("Json is invalid", IsDefined(json), false);
  }

  private cb func Test_ParseJson_Valid() {
    let json = ParseJson(this.m_json) as JsonObject;
    let pass = this.ExpectBool("Json is valid", IsDefined(json), true);

    if !pass {
      LogChannel(n"Error", "/!\\ Failed to parse Json /!\\");
      return;
    }
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
    this.ExpectJsonKeyUnicodeString("$.pangrams.Latin", pangrams, "Latin", "Sic fugiens, dux, zelotypos, quam Karus haberis.");
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

  private cb func Test_FromJson_Invalid() {
    let json = ParseJson("{key: value}") as JsonObject;
    let pass = this.ExpectBool("Parse Json fails", IsDefined(json), false);

    if !pass {
      LogChannel(n"Error", "/!\\ Parsing Json must fails /!\\");
      return;
    }
    let object = FromJson(json, n"TypesDto") as TypesDto;

    this.ExpectBool("Variant is not defined", IsDefined(object), false);
  }

  private cb func Test_FromJson_Valid() {
    let json = ParseJson(this.m_jsonDto) as JsonObject;
    let pass = this.ExpectBool("Parse Json", IsDefined(json), true);

    if !pass {
      LogChannel(n"Error", "/!\\ Failed to parse Json /!\\");
      return;
    }
    let dto = FromJson(json, n"TypesDto") as TypesDto;

    pass = this.ExpectBool("TypesDto is defined", IsDefined(dto), true);
    if !pass {
      LogChannel(n"Error", s"Failed to transform Json to Dto!");
      return;
    }
    this.ExpectBool("dto.pBool == true", dto.pBool, true);

    this.ExpectInt8("dto.pInt8 == 127", dto.pInt8, Cast<Int8>(127));
    this.ExpectInt16("dto.pInt16 == 32767", dto.pInt16, Cast<Int16>(32767));
    this.ExpectInt32("dto.pInt32 == 2147483647", dto.pInt32, 2147483647);
    this.ExpectInt64("dto.pInt64 == 9223372036854775807", dto.pInt64, 9223372036854775807l);

    this.ExpectUint8("dto.pUint8 == 255", dto.pUint8, Cast<Uint8>(255u));
    this.ExpectUint16("dto.pUint16 == 65535", dto.pUint16, Cast<Uint16>(65535u));
    this.ExpectUint32("dto.pUint32 == 4294967295", dto.pUint32, 4294967295u);
    this.ExpectUint64("dto.pUint64 == 18446744073709551615", dto.pUint64, 18446744073709551615ul);

    this.ExpectFloat("dto.pFloat == 3.141592", dto.pFloat, 3.141592);
    this.ExpectFloat("dto.pFloatInt == 1.0", dto.pFloatInt, 1.0);
    this.ExpectDouble("dto.pDouble == 3.141592653589793", dto.pDouble, 3.141592653589793d);
    this.ExpectDouble("dto.pDoubleInt == 42.0", dto.pDoubleInt, 42.0d);

    this.ExpectString("dto.pString == 'Hello world!'", dto.pString, "Hello world!");
    this.ExpectCName("dto.pCName == n'VehicleObject'", dto.pCName, n"VehicleObject");
    this.ExpectResRef("dto.pResRef == r'base\\anim_cooked.cookedanims'", dto.pResRef, r"base\\anim_cooked.cookedanims"); // Fails
    this.ExpectTweakDBID("dto.pTweakDBID == t'Items.RequiredItemStats'", dto.pTweakDBID, t"Items.RequiredItemStats");
  }

  private cb func Test_FromJson_Nested_Valid() {
    let json = ParseJson(this.m_jsonNestedDto) as JsonObject;
    let pass = this.ExpectBool("Parse Json", IsDefined(json), true);

    if !pass {
      LogChannel(n"Error", "/!\\ Failed to parse Json /!\\");
      return;
    }
    let session = FromJson(json, n"SessionDto") as SessionDto;

    pass = this.ExpectBool("session == {...}", IsDefined(session), true);
    if !pass {
      LogChannel(n"Error", s"Failed to transform Json to Dto!");
      return;
    }
    this.ExpectUint64("session.id == 1337", session.id, 1337ul);
    this.ExpectInt32("session.createdAt == 1713646202", session.createdAt, 1713646202);
    let empty = session.empty;

    this.ExpectBool("session.empty == null", IsDefined(empty), false);
    let user = session.user;

    pass = this.ExpectBool("session.user == {...}", IsDefined(user), true);
    if !pass {
      LogChannel(n"Error", s"Failed to transform Json to Dto!");
    } else {
      this.ExpectUint64("session.user.id == 42", user.id, 42ul);
      this.ExpectString("session.user.username == 'NightCity'", user.username, "NightCity");
      this.ExpectBool("session.user.isAdmin == true", user.isAdmin, true);

      this.ExpectInt32("session.user.words.length == 3", ArraySize(user.words), 3);
      this.ExpectString("session.user.words[0] == 'Hello'", user.words[0], "Hello");
      this.ExpectString("session.user.words[1] == 'world'", user.words[1], "world");
      this.ExpectString("session.user.words[2] == '!'", user.words[2], "!");

      this.ExpectInt32("session.user.i8.length == 5", ArraySize(user.i8), 5);
      this.ExpectInt8("session.user.i8[0] == -128", user.i8[0], Cast<Int8>(-128));
      this.ExpectInt8("session.user.i8[1] == -1", user.i8[1], Cast<Int8>(-1));
      this.ExpectInt8("session.user.i8[2] == 0", user.i8[2], Cast<Int8>(0));
      this.ExpectInt8("session.user.i8[3] == 1", user.i8[3], Cast<Int8>(1));
      this.ExpectInt8("session.user.i8[4] == 127", user.i8[4], Cast<Int8>(127));

      this.ExpectInt32("session.user.names.length == 3", ArraySize(user.names), 3);
      this.ExpectCName("session.user.names[0] == n'VehicleObject'", user.names[0], n"VehicleObject");
      this.ExpectCName("session.user.names[1] == n'PlayerPuppet'", user.names[1], n"PlayerPuppet");
      this.ExpectCName("session.user.names[2] == n'WeaponObject'", user.names[2], n"WeaponObject");
    }
    let friends = session.friends;

    this.ExpectBool("session.friends == [...]", true, true);
    this.ExpectInt32("session.friends.length == 4", ArraySize(friends), 4);
    if ArraySize(friends) != 4 {
      LogChannel(n"Error", s"Failed to transform Json to Dto!");
    } else {
      this.ExpectUint64("session.friends[0].id == 1", friends[0].id, 1ul);
      this.ExpectString("session.friends[0].username == \"Welles\"", friends[0].username, "Welles");
      this.ExpectUint64("session.friends[1].id == 2", friends[1].id, 2ul);
      this.ExpectString("session.friends[1].username == \"Silverhand\"", friends[1].username, "Silverhand");
      this.ExpectUint64("session.friends[2].id == 3", friends[2].id, 3ul);
      this.ExpectString("session.friends[2].username == \"Takemura\"", friends[2].username, "Takemura");
      this.ExpectUint64("session.friends[3].id == 4", friends[3].id, 4ul);
      this.ExpectString("session.friends[3].username == \"Vector\"", friends[3].username, "Vector");
    }
  }

  private cb func Test_ToJson_Invalid() {
    let json = ToJson(null);

    this.ExpectBool("To Json fails", IsDefined(json), false);
  }

  private cb func Test_ToJson_Valid() {
    let types = new TypesDto();

    types.pBool = true;
    types.pInt8 = Cast<Int8>(127); types.pInt16 = Cast<Int16>(32767); types.pInt32 = 2147483647; types.pInt64 = 9223372036854775807l;
    types.pUint8 = Cast<Uint8>(255u); types.pUint16 = Cast<Uint16>(65535u); types.pUint32 = 4294967295u; types.pUint64 = 18446744073709551615ul;
    types.pFloat = 3.141592; types.pFloatInt = 1.0; types.pDouble = 3.141592653589793d; types.pDoubleInt = 42.0d;
    types.pString = "Hello world!"; types.pCName = n"VehicleObject"; types.pResRef = r"base\\anim_cooked.cookedanims"; types.pTweakDBID = t"Items.RequiredItemStats";
    let json = ToJson(types);
    let pass = this.ExpectBool("To Json", IsDefined(json), true);

    if !pass {
      LogChannel(n"Error", "/!\\ Failed to transform to Json /!\\");
      return;
    }
    pass = this.ExpectBool("$ == {...}", json.IsObject(), true);
    if !pass {
      LogChannel(n"Error", "/!\\ JsonObject is expected in schema /!\\");
      return;
    }
    let obj = json as JsonObject;

    this.ExpectJsonKeyBool("$.pBool == true", obj, "pBool", true);

    this.ExpectJsonKeyInt64("$.pInt8 == 127", obj, "pInt8", 127);
    this.ExpectJsonKeyInt64("$.pInt16 == 32767", obj, "pInt16", 32767);
    this.ExpectJsonKeyInt64("$.pInt32 == 2147483647", obj, "pInt32", 2147483647);
    this.ExpectJsonKeyInt64("$.pInt64 == 9223372036854775807", obj, "pInt64", 9223372036854775807l);

    this.ExpectJsonKeyUint64("$.pUint8 == 255", obj, "pUint8", 255u);
    this.ExpectJsonKeyUint64("$.pUint16 == 65535", obj, "pUint16", 65535u);
    this.ExpectJsonKeyUint64("$.pUint32 == 4294967295", obj, "pUint32", 4294967295u);
    this.ExpectJsonKeyUint64("$.pUint64 == 18446744073709551615", obj, "pUint64", 18446744073709551615ul);

    this.ExpectJsonKeyDouble("$.pFloat == 3.141592", obj, "pFloat", 3.141592);
    this.ExpectJsonKeyDouble("$.pFloatInt == 1.0", obj, "pFloatInt", 1.0);
    this.ExpectJsonKeyDouble("$.pDouble == 3.141592653589793", obj, "pDouble", 3.141592653589793d);
    this.ExpectJsonKeyDouble("$.pDoubleInt == 42.0", obj, "pDoubleInt", 42.0d);

    this.ExpectJsonKeyString("$.pString == 'Hello world!'", obj, "pString", "Hello world!");
    this.ExpectJsonKeyCName("$.pCName == n'VehicleObject'", obj, "pCName", n"VehicleObject");
    /* NOTE: cannot be transformed to Json, one way only.
    this.ExpectJsonKeyResRef("$.pResRef == ''", obj, "pResRef", "");
    this.ExpectJsonKeyTweakDBID("$.pTweakDBID == ''", obj, "pTweakDBID", "");
    */
  }

  private cb func Test_ToJson_Nested_Valid() {
    let session = new SessionDto();

    session.id = 1337ul;
    session.createdAt = 1713646202;
    session.empty = null;
    session.user = new UserDto();
    session.user.id = 42ul;
    session.user.username = "NightCity";
    session.user.isAdmin = true;
    session.user.words = ["Hello", "world", "!"];
    session.user.i8 = [Cast<Int8>(-128), Cast<Int8>(-1), Cast<Int8>(0), Cast<Int8>(1), Cast<Int8>(127)];
    session.user.names = [n"VehicleObject", n"PlayerPuppet", n"WeaponObject"];
    ArrayPush(session.friends, FriendDto.Create(1ul, "Welles"));
    ArrayPush(session.friends, FriendDto.Create(2ul, "Silverhand"));
    ArrayPush(session.friends, FriendDto.Create(3ul, "Takemura"));
    ArrayPush(session.friends, FriendDto.Create(4ul, "Vector"));
    let json = ToJson(session);
    let pass = this.ExpectBool("To Json Nested", IsDefined(json), true);

    if !pass {
      LogChannel(n"Error", "/!\\ Failed to transform to Json /!\\");
      return;
    }
    pass = this.ExpectBool("$ == {...}", json.IsObject(), true);
    if !pass {
      LogChannel(n"Error", "/!\\ JsonObject is expected in schema /!\\");
      return;
    }
    let obj = json as JsonObject;

    this.ExpectJsonKeyUint64("$.id == 1337", obj, "id", 1337ul);
    this.ExpectJsonKeyInt64("$.createdAt == 1713646202", obj, "createdAt", 1713646202l);
    let empty = json.GetKey("empty");

    this.ExpectBool("$.empty == null", empty.IsNull(), true);
    let user = json.GetKey("user") as JsonObject;

    pass = this.ExpectBool("$.user == {...}", user.IsObject(), true);
    if !pass {
      LogChannel(n"Error", "/!\\ JsonObject is expected in schema /!\\");
    } else {
      this.ExpectJsonKeyUint64("$.user.id == 42", user, "id", 42ul);
      this.ExpectJsonKeyString("$.user.username == 'NightCity'", user, "username", "NightCity");
      this.ExpectJsonKeyBool("$.user.isAdmin == true", user, "isAdmin", true);
      let words = user.GetKey("words") as JsonArray;

      pass = this.ExpectBool("$.user.words == [...]", words.IsArray(), true);
      if !pass {
        LogChannel(n"Error", "/!\\ JsonArray is expected in schema /!\\");
      } else {
        this.ExpectUint32("$.user.words.length == 3", words.GetSize(), 3u);
        this.ExpectString("$.user.words[0] == 'Hello'", words.GetItemString(0u), "Hello");
        this.ExpectString("$.user.words[1] == 'world'", words.GetItemString(1u), "world");
        this.ExpectString("$.user.words[2] == '!'", words.GetItemString(2u), "!");
      }
      let i8 = user.GetKey("i8") as JsonArray;

      pass = this.ExpectBool("$.user.i8 == [...]", i8.IsArray(), true);
      if !pass {
        LogChannel(n"Error", "/!\\ JsonArray is expected in schema /!\\");
      } else {
        this.ExpectUint32("$.user.i8.length == 5", i8.GetSize(), 5u);
        this.ExpectInt64("$.user.i8[0] == -128", i8.GetItemInt64(0u), -128l);
        this.ExpectInt64("$.user.i8[1] == -1", i8.GetItemInt64(1u), -1l);
        this.ExpectInt64("$.user.i8[2] == 0", i8.GetItemInt64(2u), 0l);
        this.ExpectInt64("$.user.i8[3] == 1", i8.GetItemInt64(3u), 1l);
        this.ExpectInt64("$.user.i8[4] == 127", i8.GetItemInt64(4u), 127l);
      }
      let names = user.GetKey("names") as JsonArray;

      pass = this.ExpectBool("$.user.names == [...]", names.IsArray(), true);
      if !pass {
        LogChannel(n"Error", "/!\\ JsonArray is expected in schema /!\\");
      } else {
        this.ExpectUint32("$.user.names.length == 3", names.GetSize(), 3u);
        this.ExpectString("$.user.names[0] == n'VehicleObject'", names.GetItemString(0u), "VehicleObject");
        this.ExpectString("$.user.names[1] == n'PlayerPuppet'", names.GetItemString(1u), "PlayerPuppet");
        this.ExpectString("$.user.names[2] == n'WeaponObject'", names.GetItemString(2u), "WeaponObject");
      }
    }
    let friends = json.GetKey("friends") as JsonArray;

    pass = this.ExpectBool("$.friends == [...]", friends.IsArray(), true);
    if !pass {
      LogChannel(n"Error", "/!\\ JsonArray is expected in schema /!\\");
    } else {
      this.ExpectUint32("$.friends.length == 4", friends.GetSize(), 4u);
      if friends.GetSize() != 4u {
        LogChannel(n"Error", s"Failed to transform Dto to Json!");
      } else {
        let friend = friends.GetItem(0u) as JsonObject;

        this.ExpectJsonKeyUint64("$.friends[0].id == 1", friend, "id", 1ul);
        this.ExpectJsonKeyString("$.friends[0].username == \"Welles\"", friend, "username", "Welles");

        friend = friends.GetItem(1u) as JsonObject;
        this.ExpectJsonKeyUint64("$.friends[1].id == 2", friend, "id", 2ul);
        this.ExpectJsonKeyString("$.friends[1].username == \"Silverhand\"", friend, "username", "Silverhand");
        
        friend = friends.GetItem(2u) as JsonObject;
        this.ExpectJsonKeyUint64("$.friends[2].id == 3", friend, "id", 3ul);
        this.ExpectJsonKeyString("$.friends[2].username == \"Takemura\"", friend, "username", "Takemura");
        
        friend = friends.GetItem(3u) as JsonObject;
        this.ExpectJsonKeyUint64("$.friends[3].id == 4", friend, "id", 4ul);
        this.ExpectJsonKeyString("$.friends[3].username == \"Vector\"", friend, "username", "Vector");
      }
    }
  }

}
