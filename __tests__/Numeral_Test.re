open Jest;
open Expect;
open Numeral;

test("Should set a default format", () => {
  numeralConfig##defaultFormat("0,0");
  let num = numeral(10000.0);
  expect(num##format()) |> toEqual("10,000");
});

test("should return a value", () =>
  expect((
    numeral(1000.0)##value(),
    numeral(0.5)##value(),
    numeralString("1,000")##value(),
    numeralString("not a number")##value(),
  ))
  |> toEqual((1000.0, 0.5, Js.Nullable.return(1000.0), Js.Nullable.null))
);