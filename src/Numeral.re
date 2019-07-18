/*******************************************************************************
  Helper types
 ******************************************************************************/
type numeralJsOptions = {
  .
  "currentLocale": string,
  "zeroFormat": string,
  "nullFormat": string,
  "defaultFormat": string,
  "scalePercentBy100": bool,
};

type numeralJsLocale = {
  .
  "delimiters": {
    .
    "thousands": string,
    "decimal": string,
  },
  "abbreviations": {
    .
    "thousand": string,
    "million": string,
    "billion": string,
    "trillion": string,
  },
  "ordinal": float => string,
  "currency": {. "symbol": string},
};
type roundingFunction = float => float;

type numeralJsFormat = {
  .
  "regexps": {
    .
    "format": Js.Re.t,
    "unformat": Js.Re.t,
  },
  "format":
    (
      ~value: float,
      ~format: string,
      ~roundingFunction: roundingFunction,
      unit
    ) =>
    string,
  "unformat": (~value: string) => float,
};

/*******************************************************************************
  Main Numeral types
 ******************************************************************************/
[@bs.deriving abstract]
type t = {
  version: string,
  options: numeralJsOptions,
};
[@bs.module] external make: float => t = "numeral";
[@bs.module] external fromNumeral: t => t = "numeral";
[@bs.module] external numeral: t = "numeral";
[@bs.send] external reset: t => unit = "reset";

[@bs.send]
external registerLocale_:
  (
    t,
    ~what: [@bs.string] [ | [@bs.as "locale"] `locale],
    ~key: string,
    ~value: numeralJsLocale
  ) =>
  numeralJsLocale =
  "register";
let registerLocale = (key, value) =>
  numeral->registerLocale_(~what=`locale, ~key, ~value);
[@bs.send]
external registerFormat_:
  (
    t,
    ~what: [@bs.string] [ | [@bs.as "format"] `format],
    ~key: string,
    ~value: numeralJsFormat
  ) =>
  numeralJsFormat =
  "register";

let registerFormat = (key, value) =>
  numeral->registerFormat_(~what=`format, ~key, ~value);
[@bs.send] external locale: (t, ~key: string=?) => string = "locale";
[@bs.send]
external localeData: (t, ~key: string=?) => numeralJsLocale = "localeData";
[@bs.send] external zeroFormat: (t, string) => unit = "zeroFormat";
/* [@bs.send] external nullFormat: (t, string) => unit = "nullFormat"; */
[@bs.send] external defaultFormat: (t, string) => unit = "defaultFormat";
[@bs.send] external clone: t => t = "clone";
[@bs.send]
external format:
  (t, ~format: string=?, ~roundingFunction: roundingFunction=?, unit) => string =
  "format";
[@bs.send] external unformat: (t, string) => float = "unformat";
[@bs.send] external value: t => float = "value";
/* [@bs.send] external valueOf: t => float = "valueOf"; */
[@bs.send] external set: (t, float) => t = "set";
[@bs.send] external add: (t, 'a) => t = "add";
[@bs.send] external subtract: (t, 'a) => t = "subtract";
[@bs.send] external multiply: (t, 'a) => t = "multiply";
[@bs.send] external divide: (t, 'a) => t = "divide";
[@bs.send] external difference: (t, 'a) => float = "difference";
[@bs.send] external validate_: (t, 'a, 'b) => bool = "validate";
let validate = (a, b) => numeral->validate_(a, b);

/*
  This is the same as the regular type except that it takes strings instead of
  floats and it returns options.
*/
module String = {
  [@bs.deriving abstract]
  type t = {
    version: string,
    options: numeralJsOptions,
  };
  [@bs.module] external make: string => t = "numeral";
  [@bs.module] external fromNumeral: t => t = "numeral";
  [@bs.module] external numeral: t = "numeral";
  [@bs.send] external reset: t => unit = "reset";
  [@bs.send]
  external registerLocale_:
    (
      t,
      ~what: [@bs.string] [ | [@bs.as "locale"] `locale],
      ~key: string,
      ~value: numeralJsLocale
    ) =>
    numeralJsLocale =
    "register";
  let registerLocale = (~key, ~value) =>
    numeral->registerLocale_(~what=`locale, ~key, ~value);
  [@bs.send]
  external registerFormat_:
    (
      t,
      ~what: [@bs.string] [ | [@bs.as "format"] `format],
      ~key: string,
      ~value: numeralJsFormat
    ) =>
    numeralJsFormat =
    "register";
  let registerFormat = (~key, ~value) =>
    numeral->registerFormat_(~what=`format, ~key, ~value);
  [@bs.send] external locale: (t, ~key: string=?) => string = "locale";
  [@bs.send]
  external localeData: (t, ~key: string=?) => numeralJsLocale = "localeData";
  [@bs.send] external zeroFormat: (t, string) => unit = "zeroFormat";
  /* [@bs.send] external nullFormat: (t, string) => unit = "nullFormat"; */
  [@bs.send] external defaultFormat: (t, string) => unit = "defaultFormat";
  [@bs.send] external clone: t => t = "clone";
  [@bs.send]
  external format:
    (t, ~format: string=?, ~roundingFunction: roundingFunction=?, unit) =>
    string =
    "format";
  [@bs.send] external unformat: (t, string) => float = "unformat";
  [@bs.send] external value_: t => Js.Nullable.t(float) = "value";
  let value = t => t->value_->Js.Nullable.toOption;
  /* [@bs.send] external valueOf_: t => Js.Nullable.t(float) = "valueOf";
     let valueOf = t => t->valueOf_->Js.Nullable.toOption; */
  [@bs.send] external set: (t, string) => t = "set";
  [@bs.send] external add: (t, 'a) => t = "add";
  [@bs.send] external subtract: (t, 'a) => t = "subtract";
  [@bs.send] external multiply: (t, 'a) => t = "multiply";
  [@bs.send] external divide: (t, 'a) => t = "divide";
  [@bs.send]
  external difference_: (t, 'a) => Js.Nullable.t(float) = "difference";
  let difference = (t, value) => t->difference_(value)->Js.Nullable.toOption;
  [@bs.send] external validate_: (t, 'a, 'b) => bool = "validate";
  let validate = (a, b) => numeral->validate_(a, b);
};

module Helpers = {
  type helper = {
    .
    [@bs.meth] "numberToFormat": (float, string, roundingFunction) => string,
    [@bs.meth] "stringToNumber": string => float,
    [@bs.meth] "includes": (string, string) => bool,
    [@bs.meth] "insert": (string, string, int) => string,
    [@bs.meth] "multiplier": string => float,
    [@bs.meth] "correctionFactor": float => float,
    [@bs.meth] "toFixed": (float, int, roundingFunction, int) => float,
  };
  /* TODO: this hack isn't guaranteed to work. */
  [@bs.val] external helper: helper = "Numeral._";
  let numberToFormat = (~value, ~format, ~roundingFunction) =>
    helper##numberToFormat(value, format, roundingFunction);
  let stringToNumber = value => helper##stringToNumber(value);
  let includes = (string, search) => helper##includes(string, search);
  let insert = (string, subString, start) =>
    helper##insert(string, subString, start);
  let multiplier = x => helper##multiplier(x);
  let correctionFactor = arg => helper##correctionFactor(arg);
  let toFixed = (value, maxDecimals, roundingFunction, optionals) =>
    helper##toFixed(value, maxDecimals, roundingFunction, optionals);
};