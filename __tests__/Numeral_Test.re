open Jest;
open Expect;
open Numeral;
/* This is based on the actual test that Numeral uses. It's heavily trimmed. We
   are only interested in ensuring that the methods are bound correctly, not
   necessarily with their output.*/
describe("Numeral", () => {
  afterEach(() => reset(numeral));

  test("It should set a default format", () => {
    setDefaultFormat("0,0");
    expect(make(10000.0)->formatDefault) |> toEqual("10,000");
  });

  test("It should return a value", () =>
    expect(make(1000.0)->value) |> toEqual(1000.0)
  );

  test("It should return a value (String)", () =>
    expect((
      String.make("1,000")->String.value,
      String.make("not a number")->String.value,
    ))
    |> toEqual((Some(1000.0), None))
  );

  describe("Types", () => {
    test("It should return a value as correct type", () =>
      expect((
        make(1234.56)->value->Js.Types.test(Js.Types.Number),
        make(0.0)->value->Js.Types.test(Js.Types.Number),
        make(Js.Float._NaN)->value->Js.Types.test(Js.Types.Object),
      ))
      |> toEqual((true, true, true))
    );
    test("It should return a value as correct type (String)", () =>
      expect(
        String.make("1234.56")->String.value->Js.Types.test(Js.Types.Number),
      )
      |> toEqual(true)
    );
  });

  describe("Value", () => {
    test("It should return a value", () =>
      expect(make(1000.0)->value) |> toEqual(1000.0)
    );

    test("It should return a value (String)", () =>
      expect((
        String.make("1,000")->String.value,
        String.make("not a number")->String.value,
      ))
      |> toEqual((Some(1000.0), None))
    );
  });

  describe("Set", () =>
    test("It should set a value", () =>
      expect(make(0.0)->set(1000.0)->value) |> toEqual(1000.0)
    )
  );

  describe("Custom Zero", () =>
    test("It should change zero value", () => {
      setZeroFormat("N/A");
      let a = make(0.0)->format("0");
      setZeroFormat("");
      let b = make(0.0)->format("");
      expect((a, b)) |> toEqual(("N/A", ""));
    })
  );
  describe("Clone", () =>
    test("It should clone", () => {
      let a = make(1000.0);
      let b = fromNumeral(a);
      let c = clone(a);
      let aVal = value(a);
      let aSet = a->set(2000.0)->value;
      let bVal = value(b);
      let cVal = c->add(10.0)->value;
      expect((aVal, aSet, bVal, cVal))
      |> toEqual((1000.0, 2000.0, 1000.0, 1010.0));
    })
  );

  describe("Format", () =>
    test("It should format to a number", () =>
      expect((
        make(0.0)->format("0.00"),
        make(Js.Float._NaN)->format("0.0"),
      ))
      |> toEqual(("0.00", "0.0"))
    )
  );

  describe("Unformat", () => {
    /* This one doesn't do anything, I think.*/
    test("It should unformat a number", () => {
      setZeroFormat("N/A");
      let result = make(0.0)->value;
      reset(numeral);
      expect(result) |> toEqual(0.0);
    });
    /* Unformat is only used for strings. */
    test("It should unformat a number (String)", () => {
      setZeroFormat("N/A");
      expect((
        String.make("1.23t")->String.value,
        String.make("N/A")->String.value,
        String.make("")->String.value,
      ))
      |> toEqual((Some(1230000000000.0), Some(0.0), None));
    });
  });

  describe("Validate", () => {
    let locale = "en";

    describe("Numbers", () =>
      test("It should validate numbers", () =>
        expect((validate("1000", locale), validate("1.0,00", locale)))
        |> toEqual((true, false))
      )
    );

    describe("Currency", () =>
      test("It should validate currency", () =>
        expect((validate("$1000", locale), validate("%100", locale)))
        |> toEqual((true, false))
      )
    );
  });
  describe("Manipulate", () =>
    describe("Add", () =>
      test("It should add", () =>
        expect(make(1000.0)->add(10.0)->value) |> toEqual(1010.0)
      )
    )
  );
  describe("Subtract", () =>
    test("It should subtract", () =>
      expect(make(1000.0)->subtract(10.)->value) |> toEqual(990.0)
    )
  );
  describe("Multiply", () =>
    test("It should multiply", () =>
      expect(make(1000.0)->multiply(10.)->value) |> toEqual(10000.0)
    )
  );
  describe("Divide", () =>
    test("It should divide", () =>
      expect(make(1000.0)->divide(10.)->value) |> toEqual(100.0)
    )
  );

  describe("Difference", () =>
    test("It should find a difference", () =>
      expect(make(1000.0)->difference(10.)) |> toEqual(990.0)
    )
  );
  describe("Rounding", () =>
    test("It should format with rounding", () => {
      let num = make(2280002.0);
      expect((
        formatRound(num, "0.00a", floor),
        formatRound(num, "0.00a", ceil),
      ))
      |> toEqual(("2.28m", "2.29m"));
    })
  );
  describe("Utilities", () =>
    describe("Insert", () =>
      test("It should insert into string", () =>
        expect(Helpers.insert("1000", "+", 0)) |> toEqual("+1000")
      )
    )
  );
  test("Can register a custom format", () => {
    registerFormat(
      "percentage2",
      Format.make(
        ~regexps=
          RegExps.make(
            ~format=[%bs.re "/(test)/"],
            ~unformat=[%bs.re "/(test)/"],
          ),
        ~formatFn=
          (value, format, roundingFunction) => {
            let space = Helpers.includes(format, " %") ? " " : "";
            let value = value *. 100.0;
            /* check for space before % */
            let format2 =
              format |> Js.String.replaceByRe([%bs.re "/\\s?\\%/"], "");
            let output =
              Helpers.numberToFormat(
                ~value,
                ~format=format2,
                ~roundingFunction,
              );
            if (Helpers.includes(output, ")")) {
              output
              |> Js.String.split("")
              |> Js.Array.concat([|space ++ "%"|])
              |> Js.Array.joinWith("");
            } else {
              output ++ space ++ "%";
            };
          },
        ~unformatFn=value => Helpers.stringToNumber(value) *. 0.01,
      ),
    )
    |> ignore;
    expect(make(0.42)->format("test")) |> toBe("42%");
  });
  test("The example works", () => {
    let initialProgress = 0.42;
    let growth =
      "165%"
      ->Numeral.String.make
      ->Numeral.String.value
      ->Belt.Option.getWithDefault(1.0);
    let output =
      initialProgress
      ->Numeral.make
      ->Numeral.multiply(growth)
      ->Numeral.format("%");
    expect(output) |> toBe("69%");
  });
  describe("Type testing", () =>
    test("It can parse integers", () =>
      expect(fromInt(1)->value) |> toBe(1.0)
    )
  );
});