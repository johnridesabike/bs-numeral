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
  "format": (float, string, roundingFunction) => string,
  "unformat": string => float,
};

/*******************************************************************************
  The base numeral object
 ******************************************************************************/
[@bs.deriving abstract]
type numeral = {
  version: string,
  options: numeralJsOptions,
};
[@bs.module] external numeral: numeral = "numeral";
[@bs.send] external reset: numeral => unit = "reset";
[@bs.send]
external registerLocale_:
  (numeral, ~what: string, ~key: string, ~value: numeralJsLocale) =>
  numeralJsLocale =
  "register";
let registerLocale = (key, value) =>
  numeral->registerLocale_(~what="locale", ~key, ~value);
[@bs.send]
external registerFormat_:
  (numeral, ~what: string, ~key: string, ~value: numeralJsFormat) =>
  numeralJsFormat =
  "register";

let registerFormat = (key, value) =>
  numeral->registerFormat_(~what="format", ~key, ~value);
[@bs.send] external locale_: (numeral, ~key: string=?) => string = "locale";
let locale = (~key) => numeral->locale_(~key);
[@bs.send]
external localeData_: (numeral, ~key: string=?) => numeralJsLocale =
  "localeData";
let localeData = (~key) => numeral->localeData_(~key);
[@bs.send] external zeroFormat_: (numeral, string) => unit = "zeroFormat";
let zeroFormat = str => numeral->zeroFormat_(str);
/* [@bs.send] external nullFormat: (t, string) => unit = "nullFormat"; */
[@bs.send]
external setDefaultFormat_: (numeral, string) => unit = "defaultFormat";
let setDefaultFormat = str => numeral->setDefaultFormat_(str);
[@bs.send] external validate_: (numeral, 'a, 'b) => bool = "validate";
let validate = (a, b) => numeral->validate_(a, b);

/*******************************************************************************
  Numeral instances
 ******************************************************************************/
type t;
[@bs.module] external make: float => t = "numeral";
[@bs.module] external fromNumeral: t => t = "numeral";
[@bs.send] external clone: t => t = "clone";
[@bs.send] external formatDefault: t => string = "format";
[@bs.send] external format: (t, string) => string = "format";
[@bs.send]
external formatRound: (t, string, roundingFunction) => string = "format";
[@bs.send] external unformat: (t, string) => float = "unformat";
[@bs.send] external value: t => float = "value";
/* [@bs.send] external valueOf: t => float = "valueOf"; */
[@bs.send] external set: (t, float) => t = "set";
[@bs.send] external add: (t, 'a) => t = "add";
[@bs.send] external subtract: (t, 'a) => t = "subtract";
[@bs.send] external multiply: (t, 'a) => t = "multiply";
[@bs.send] external divide: (t, 'a) => t = "divide";
[@bs.send] external difference: (t, 'a) => float = "difference";

/*
   This is the same as the regular type except that it takes strings instead of
   floats and it returns options.
 */
module String = {
  /*****************************************************************************
    The base numeral object
   ****************************************************************************/
  [@bs.deriving abstract]
  type numeral = {
    version: string,
    options: numeralJsOptions,
  };
  [@bs.module] external numeral: numeral = "numeral";
  [@bs.send] external reset: numeral => unit = "reset";
  [@bs.send]
  external registerLocale_:
    (numeral, ~what: string, ~key: string, ~value: numeralJsLocale) =>
    numeralJsLocale =
    "register";
  let registerLocale = (~key, ~value) =>
    numeral->registerLocale_(~what="locale", ~key, ~value);
  [@bs.send]
  external registerFormat_:
    (numeral, ~what: string, ~key: string, ~value: numeralJsFormat) =>
    numeralJsFormat =
    "register";
  let registerFormat = (~key, ~value) =>
    numeral->registerFormat_(~what="format", ~key, ~value);
  [@bs.send] external locale_: (numeral, ~key: string=?) => string = "locale";
  let locale = (~key) => numeral->locale_(~key);
  [@bs.send]
  external localeData_: (numeral, ~key: string=?) => numeralJsLocale =
    "localeData";
  let localeData = (~key) => numeral->localeData_(~key);
  [@bs.send] external zeroFormat: (numeral, string) => unit = "zeroFormat";
  /* [@bs.send] external nullFormat: (numeral, string) => unit = "nullFormat"; */
  [@bs.send]
  external setDefaultFormat: (numeral, string) => unit = "defaultFormat";
  [@bs.send] external validate_: (numeral, 'a, 'b) => bool = "validate";
  let validate = (a, b) => numeral->validate_(a, b);
  /*****************************************************************************
    Numeral instances
   ****************************************************************************/
  type t;
  [@bs.module] external make: string => t = "numeral";
  [@bs.module] external fromNumeral: t => t = "numeral";
  [@bs.send] external clone: t => t = "clone";
  [@bs.send] external formatDefault: t => string = "format";
  [@bs.send] external format: (t, string) => string = "format";
  [@bs.send]
  external formatRound: (t, string, roundingFunction) => string = "format";
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
};

/*
   These bindings aren't well tested or documented. Use with caution.
   Pull requests and bug reports are welcome!
 */
module Helpers = {
  type t;
  [@bs.get] external getHelpers: numeral => t = "_";

  type numberToFormat = (float, string, roundingFunction) => string;
  [@bs.get] external getNumberToFormat: t => numberToFormat = "numberToFormat";
  let numberToFormat = (~value, ~format, ~roundingFunction) =>
    numeral->getHelpers->getNumberToFormat(value, format, roundingFunction);

  type stringToNumber = string => float;
  [@bs.get] external getStringToNumber: t => stringToNumber = "stringToNumber";
  let stringToNumber = value => numeral->getHelpers->getStringToNumber(value);

  type includes = (string, string) => bool;
  [@bs.get] external getIncludes: t => includes = "includes";
  let includes = (string, search) =>
    numeral->getHelpers->getIncludes(string, search);

  type insert = (string, string, int) => string;
  [@bs.get] external getInsert: t => insert = "insert";
  let insert = (string, subString, start) =>
    numeral->getHelpers->getInsert(string, subString, start);

  type multiplier = string => float;
  [@bs.get] external getMultiplier: t => multiplier = "multiplier";
  let multiplier = x => numeral->getHelpers->getMultiplier(x);

  type correctionFactor1 = float => float;
  type correctionFactor2 = (float, float) => float;
  type correctionFactor3 = (float, float, float) => float;
  type correctionFactor4 = (float, float, float, float) => float;
  type correctionFactor5 = (float, float, float, float, float) => float;
  [@bs.get]
  external getCorrectionFactor1: t => correctionFactor1 = "correctionFactor";
  [@bs.get]
  external getCorrectionFactor2: t => correctionFactor2 = "correctionFactor";
  [@bs.get]
  external getCorrectionFactor3: t => correctionFactor3 = "correctionFactor";
  [@bs.get]
  external getCorrectionFactor4: t => correctionFactor4 = "correctionFactor";
  [@bs.get]
  external getCorrectionFactor5: t => correctionFactor5 = "correctionFactor";
  let correctionFactor1 = arg1 =>
    numeral->getHelpers->getCorrectionFactor1(arg1);
  let correctionFactor2 = (arg1, arg2) =>
    numeral->getHelpers->getCorrectionFactor2(arg1, arg2);
  let correctionFactor3 = (arg1, arg2, arg3) =>
    numeral->getHelpers->getCorrectionFactor3(arg1, arg2, arg3);
  let correctionFactor4 = (arg1, arg2, arg3, arg4) =>
    numeral->getHelpers->getCorrectionFactor4(arg1, arg2, arg3, arg4);
  let correctionFactor5 = (arg1, arg2, arg3, arg4, arg5) =>
    numeral->getHelpers->getCorrectionFactor5(arg1, arg2, arg3, arg4, arg5);

  type toFixed = (float, int, roundingFunction, int) => float;
  [@bs.get] external getToFixed: t => toFixed = "toFixed";
  let toFixed = (value, maxDecimals, roundingFunction, optionals) =>
    numeral
    ->getHelpers
    ->getToFixed(value, maxDecimals, roundingFunction, optionals);
};