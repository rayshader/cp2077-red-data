import RedData.Json.*

public class JsonArrayTest extends JsonBaseTest {

  public func Create() {
    this.m_modName = "RedData";
    this.m_name = "JsonArray";
  }

  private cb func Test_Constructor() {
    let array = new JsonArray();

    this.ExpectBool("Constructor is array", array.IsArray(), true);
    this.ExpectBool("Constructor is empty", array.GetSize() == 0u, true);
    this.ExpectBool("Constructor $[0] is null", IsDefined(array.GetItem(0u)), false);

    array.SetItem(0u, new JsonObject());
    this.ExpectBool("Constructor $[0] = true is ignored", array.GetSize() == 0u, true);
  }

  private cb func Test_AddItems() {
    let array = new JsonArray();

    array.AddItemNull();
    array.AddItemBool(false);
    array.AddItemInt64(9223372036854775807l);
    array.AddItemUint64(18446744073709551615ul);
    array.AddItemDouble(2.12);
    array.AddItemString("Choom");

    this.ExpectBool("AddItems $.size == 6", array.GetSize() == 6u, true);

    this.ExpectBool("AddItems $[0] == null", array.GetItem(0u).IsNull(), true);
    this.ExpectBool("AddItems $[1] == false", array.GetItemBool(1u), false);
    this.ExpectInt64("AddItems $[2] == 9223372036854775807", array.GetItemInt64(2u), 9223372036854775807l);
    this.ExpectUint64("AddItems $[3] == 18446744073709551615", array.GetItemUint64(3u), 18446744073709551615ul);
    this.ExpectDouble("AddItems $[4] == 2.12", array.GetItemDouble(4u), 2.12);
    this.ExpectString("AddItems $[5] == \"Choom\"", array.GetItemString(5u), "Choom");
  }

  private cb func Test_SetItems() {
    let array = new JsonArray();

    array.AddItemNull();
    array.AddItemBool(false);
    array.AddItemInt64(9223372036854775807l);
    array.AddItemUint64(18446744073709551615ul);
    array.AddItemDouble(2.12);
    array.AddItemString("Choom");

    array.SetItemString(0u, "Choom");
    array.SetItemDouble(1u, 2.12);
    array.SetItemUint64(2u, 18446744073709551615ul);
    array.SetItemInt64(3u, 9223372036854775807l);
    array.SetItemBool(4u, false);
    array.SetItemNull(5u);

    this.ExpectBool("SetItems $.size == 6", array.GetSize() == 6u, true);

    this.ExpectString("SetItems $[0] == \"Choom\"", array.GetItemString(0u), "Choom");
    this.ExpectDouble("SetItems $[1] == 2.12", array.GetItemDouble(1u), 2.12);
    this.ExpectUint64("SetItems $[2] == 18446744073709551615", array.GetItemUint64(2u), 18446744073709551615ul);
    this.ExpectInt64("SetItems $[3] == 9223372036854775807", array.GetItemInt64(3u), 9223372036854775807l);
    this.ExpectBool("SetItems $[4] == false", array.GetItemBool(4u), false);
    this.ExpectBool("SetItems $[5] == null", array.GetItem(5u).IsNull(), true);
  }

  private cb func Test_InsertItems() {
    let array = new JsonArray();

    array.AddItemNull();
    array.AddItemBool(false);
    array.AddItemInt64(9223372036854775807l);
    array.AddItemUint64(18446744073709551615ul);
    array.AddItemDouble(2.12);
    array.AddItemString("Choom");

    array.InsertItemString(5u, "Choom");
    array.InsertItemDouble(4u, 2.12);
    array.InsertItemUint64(3u, 18446744073709551615ul);
    array.InsertItemInt64(2u, 9223372036854775807l);
    array.InsertItemBool(1u, false);
    array.InsertItemNull(0u);

    this.ExpectBool("InsertItems $.size == 12", array.GetSize() == 12u, true);

    this.ExpectBool("InsertItems $[0] == null", array.GetItem(0u).IsNull(), true);
    this.ExpectBool("InsertItems $[1] == null", array.GetItem(1u).IsNull(), true);
    this.ExpectBool("InsertItems $[2] == false", array.GetItemBool(2u), false);
    this.ExpectBool("InsertItems $[3] == false", array.GetItemBool(3u), false);
    this.ExpectInt64("InsertItems $[4] == 9223372036854775807", array.GetItemInt64(4u), 9223372036854775807l);
    this.ExpectInt64("InsertItems $[5] == 9223372036854775807", array.GetItemInt64(5u), 9223372036854775807l);
    this.ExpectUint64("InsertItems $[6] == 18446744073709551615", array.GetItemUint64(6u), 18446744073709551615ul);
    this.ExpectUint64("InsertItems $[7] == 18446744073709551615", array.GetItemUint64(7u), 18446744073709551615ul);
    this.ExpectDouble("InsertItems $[8] == 2.12", array.GetItemDouble(8u), 2.12);
    this.ExpectDouble("InsertItems $[9] == 2.12", array.GetItemDouble(9u), 2.12);
    this.ExpectString("InsertItems $[10] == \"Choom\"", array.GetItemString(10u), "Choom");
    this.ExpectString("InsertItems $[11] == \"Choom\"", array.GetItemString(11u), "Choom");
  }

  private cb func Test_RemoveItems() {
    let array = new JsonArray();

    array.AddItemNull();
    array.AddItemBool(false);
    array.AddItemInt64(9223372036854775807l);
    array.AddItemUint64(18446744073709551615ul);
    array.AddItemDouble(2.12);
    array.AddItemString("Choom");

    this.ExpectBool("RemoveItems $.size == 6", array.GetSize() == 6u, true);
    this.ExpectBool("RemoveItems $[0] == null", array.GetItem(0u).IsNull(), true);

    array.RemoveItem(0u);
    this.ExpectBool("RemoveItems $[0] == false", array.GetItemBool(0u), false);

    array.RemoveItem(0u);
    this.ExpectInt64("RemoveItems $[0] == 9223372036854775807", array.GetItemInt64(0u), 9223372036854775807l);

    array.RemoveItem(0u);
    this.ExpectUint64("RemoveItems $[0] == 18446744073709551615", array.GetItemUint64(0u), 18446744073709551615ul);

    array.RemoveItem(0u);
    this.ExpectDouble("RemoveItems $[0] == 2.12", array.GetItemDouble(0u), 2.12);

    array.RemoveItem(0u);
    this.ExpectString("RemoveItems $[0] == \"Choom\"", array.GetItemString(0u), "Choom");

    array.RemoveItem(0u);
    this.ExpectBool("RemoveItems $.size == 0", array.GetSize() == 0u, true);
  }

  private cb func Test_Clear() {
    let array = new JsonArray();

    array.AddItemNull();
    array.AddItemBool(false);
    array.AddItemInt64(9223372036854775807l);
    array.AddItemUint64(18446744073709551615ul);
    array.AddItemDouble(2.12);
    array.AddItemString("Choom");
    this.ExpectBool("Clear $.size == 6", array.GetSize() == 6u, true);

    array.Clear();

    this.ExpectBool("Clear $.size == 0", array.GetSize() == 0u, true);
  }

}
