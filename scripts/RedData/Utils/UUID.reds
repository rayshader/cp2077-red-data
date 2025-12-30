module RedData

public native struct UUID {
  public native static func Generate() -> UUID;
  public native static func Equals(a: UUID, b: UUID) -> Bool;
  public native static func IsValid(value: UUID) -> Bool;
  public native static func FromString(value: String) -> UUID;
  public native static func ToString(value: UUID) -> String;
}

public func OperatorEqual(a: UUID, b: UUID) -> Bool = UUID.Equals(a, b);
public func OperatorNotEqual(a: UUID, b: UUID) -> Bool = !UUID.Equals(a, b);
