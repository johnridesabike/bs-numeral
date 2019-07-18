open Jest;
open Expect;
open Numeral;

/*
   Takes a list of tuples of (result, expectedResult) and reduces them into a
   a tuple of two lists for easy comparison.
 */

describe("Numeral", () => {
  afterEach(() => numeral->reset);

  test("It should set a default format", () => {
    numeral->defaultFormat("0,0");
    expect(make(10000.0)->format()) |> toEqual("10,000");
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
      let tests = [(0.0, "N/A", "0", "N/A"), (0.0, "", "", "")];
      let (results, expectedResults) =
        tests->Belt.List.reduce(
          ([], []),
          ((y, z), (inputvalue, formatstr, str, expectedResult)) => {
            numeral->zeroFormat(formatstr);
            (
              [make(inputvalue)->format(~format=str, ()), ...y],
              [expectedResult, ...z],
            );
          },
        );
      expect(results) |> toEqual(expectedResults);
    })
  );
  describe("Clone", () =>
    test("It should clone", () => {
      let a = make(1000.0);
      let b = fromNumeral(a);
      let c = a->clone;
      let aVal = a->value;
      let aSet = a->set(2000.0)->value;
      let bVal = b->value;
      let cVal = c->add(10.0)->value;

      expect((aVal, aSet, bVal, cVal))
      |> toEqual((1000.0, 2000.0, 1000.0, 1010.0));
    })
  );

  describe("Format", () =>
    test("It should format to a number", () =>
      expect((
        make(0.0)->format(~format="0.00", ()),
        make(Js.Float._NaN)->format(~format="0.0", ()),
      ))
      |> toEqual(("0.00", "0.0"))
    )
  );

  describe("Unformat", () => {
    /*
       This one doesn't do anything, I think.
     */
    test("It should unformat a number", () => {
      numeral->zeroFormat("N/A");
      let result = make(0.0)->value;
      numeral->reset;
      expect(result) |> toEqual(0.0);
    });
    /*
       Unformat is only used for strings.
     */
    test("It should unformat a number (String)", () => {
      numeral->zeroFormat("N/A");
      expect((
        String.make("1.23t")->String.value,
        String.make("N/A")->String.value,
        String.make("")->String.value,
      ))
      |> toEqual((Some(1230000000000.0), Some(0.0), None));
    });
    numeral->reset;
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
      expect(make(1000.0)->subtract(10)->value) |> toEqual(990.0)
    )
  );
  describe("Multiply", () =>
    test("It should multiply", () =>
      expect(make(1000.0)->multiply(10)->value) |> toEqual(10000.0)
    )
  );
  describe("Divide", () =>
    test("It should divide", () =>
      expect(make(1000.0)->divide(10)->value) |> toEqual(100.0)
    )
  );

  describe("Difference", () =>
    test("It should find a difference", () =>
      expect(make(1000.0)->difference(10)) |> toEqual(990.0)
    )
  );
  describe("Rounding", () =>
    test("It should format with rounding", () => {
      let num = make(2280002.0);
      expect((
        num->format(~format="0.00a", ~roundingFunction=floor, ()),
        num->format(~format="0.00a", ~roundingFunction=ceil, ()),
      ))
      |> toEqual(("2.28m", "2.29m"));
    })
  );
  /*
   I'm not gonna bind the utility functions for now.
   describe("Utilities", () =>  {
       describe("Insert", () =>  {
           test("It should insert into string", () =>  {
               var tests = [
                       ["1000", "+", 0, "+1000"],
                       ["1000", "-", 4, "1000-"]
                   ],
                   i;

               for (i = 0; i < tests.length; i++) {
                   expect(numeral._.insert(tests[i][0], tests[i][1], tests[i][2])).toEqual(tests[i][3]);
               }

           });
       });
   }); */
  test("Can register a custom format", () => {
    let _ =
      registerFormat(
        "percentage2",
        {
          "regexps": {
            "format": Js.Re.fromString("(test)"),
            "unformat": Js.Re.fromString("(test)"),
          },
          "format":
            (
              ~value: float,
              ~format: string,
              ~roundingFunction: roundingFunction,
              (),
            ) => {
            let space = Helpers.includes(format, " %") ? " " : "";
            let value = value *. 100.0;
            // check for space before %
            let format2 =
              format
              |> Js.String.replaceByRe(Js.Re.fromString("/\s?\%/"), "");
            let output =
              Helpers.numberToFormat(
                ~value,
                ~format=format2,
                ~roundingFunction,
              );
            if (output->Helpers.includes(")")) {
              output
              |> Js.String.split("")
              |> Js.Array.concat([|space ++ "%"|])
              |> Js.Array.joinWith("");
            } else {
              output ++ space ++ "%";
            };
          },
          "unformat": (~value: string) => {
            Helpers.stringToNumber(value) *. 0.01;
          },
        },
      );
    expect(make(0.0)->format(~format="test", ())) |> toBe("0%");
  });
});