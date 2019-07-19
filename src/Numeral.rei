type numeralJsOptions =
    {. "currentLocale": string, "defaultFormat": string,
      "nullFormat": string, "scalePercentBy100": bool, "zeroFormat": 
      string};
type numeralJsLocale =
    {. "abbreviations": {. "billion": string, "million": string,
                          "thousand": string, "trillion": string},
      "currency": {. "symbol": string},
      "delimiters": {. "decimal": string, "thousands": string},
      "ordinal": float => string};
type roundingFunction = float => float;
type numeralJsFormat =
    {. "format": (float, string, roundingFunction) => string,
      "regexps": {. "format": Js.Re.t, "unformat": Js.Re.t},
      "unformat": string => float};
type numeral;
let version: numeral => string;
let versionGet: numeral => string;
let options: numeral => numeralJsOptions;
let optionsGet: numeral => numeralJsOptions;
[@bs.module "numeral"] external numeral: numeral = "default";
[@bs.send] external reset: numeral => unit = "reset";
[@bs.send] external registerLocale_:
  (numeral, ~what: string, ~key: string, ~value: numeralJsLocale) =>
  numeralJsLocale = "register";
let registerLocale: (string, numeralJsLocale) => numeralJsLocale;
[@bs.send] external registerFormat_:
  (numeral, ~what: string, ~key: string, ~value: numeralJsFormat) =>
  numeralJsFormat = "register";
let registerFormat: (string, numeralJsFormat) => numeralJsFormat;
[@bs.send] external locale_: (numeral, ~key: string=?) => string = "locale";
let locale: (~key: string) => string;
[@bs.send] external localeData_: (numeral, ~key: string=?) => numeralJsLocale
  = "localeData";
let localeData: (~key: string) => numeralJsLocale;
[@bs.send] external zeroFormat_: (numeral, string) => unit = "zeroFormat";
let zeroFormat: string => unit;
[@bs.send] external setDefaultFormat_: (numeral, string) => unit
  = "defaultFormat";
let setDefaultFormat: string => unit;
[@bs.send] external validate_: (numeral, 'a, 'b) => bool = "validate";
let validate: ('a, 'b) => bool;
type t;
[@bs.module "numeral"] external make: float => t = "default";
[@bs.module "numeral"] external fromNumeral: t => t = "default";
[@bs.send] external clone: t => t = "clone";
[@bs.send] external formatDefault: t => string = "format";
[@bs.send] external format: (t, string) => string = "format";
[@bs.send] external formatRound: (t, string, roundingFunction) => string
  = "format";
[@bs.send] external unformat: (t, string) => float = "unformat";
[@bs.send] external value: t => float = "value";
[@bs.send] external set: (t, float) => t = "set";
[@bs.send] external add: (t, 'a) => t = "add";
[@bs.send] external subtract: (t, 'a) => t = "subtract";
[@bs.send] external multiply: (t, 'a) => t = "multiply";
[@bs.send] external divide: (t, 'a) => t = "divide";
[@bs.send] external difference: (t, 'a) => float = "difference";
module String:
  {
    type numeral;
    let version: numeral => string;
    let versionGet: numeral => string;
    let options: numeral => numeralJsOptions;
    let optionsGet: numeral => numeralJsOptions;
    [@bs.module "numeral"] external numeral: numeral = "default";
    [@bs.send] external reset: numeral => unit = "reset";
    [@bs.send] external registerLocale_:
      (numeral, ~what: string, ~key: string, ~value: numeralJsLocale) =>
      numeralJsLocale = "register";
    let registerLocale:
      (~key: string, ~value: numeralJsLocale) => numeralJsLocale;
    [@bs.send] external registerFormat_:
      (numeral, ~what: string, ~key: string, ~value: numeralJsFormat) =>
      numeralJsFormat = "register";
    let registerFormat:
      (~key: string, ~value: numeralJsFormat) => numeralJsFormat;
    [@bs.send] external locale_: (numeral, ~key: string=?) => string = "locale";
    let locale: (~key: string) => string;
    [@bs.send] external localeData_:
      (numeral, ~key: string=?) => numeralJsLocale = "localeData";
    let localeData: (~key: string) => numeralJsLocale;
    [@bs.send] external zeroFormat: (numeral, string) => unit = "zeroFormat";
    [@bs.send] external setDefaultFormat: (numeral, string) => unit
      = "defaultFormat";
    [@bs.send] external validate_: (numeral, 'a, 'b) => bool = "validate";
    let validate: ('a, 'b) => bool;
    type t;
    [@bs.module "numeral"] external make: string => t = "default";
    [@bs.module "numeral"] external fromNumeral: t => t = "default";
    [@bs.send] external clone: t => t = "clone";
    [@bs.send] external formatDefault: t => string = "format";
    [@bs.send] external format: (t, string) => string = "format";
    [@bs.send] external formatRound: (t, string, roundingFunction) => string
      = "format";
    [@bs.send] external unformat: (t, string) => float = "unformat";
    [@bs.send] external value_: t => Js.Nullable.t(float) = "value";
    let value: t => option(float);
    [@bs.send] external set: (t, string) => t = "set";
    [@bs.send] external add: (t, 'a) => t = "add";
    [@bs.send] external subtract: (t, 'a) => t = "subtract";
    [@bs.send] external multiply: (t, 'a) => t = "multiply";
    [@bs.send] external divide: (t, 'a) => t = "divide";
    [@bs.send] external difference_: (t, 'a) => Js.Nullable.t(float)
      = "difference";
    let difference: (t, 'a) => option(float);
  };
module Helpers:
  {
    type t;
    [@bs.get] external getHelpers: numeral => t = "_";
    type numberToFormat = (float, string, roundingFunction) => string;
    [@bs.get] external getNumberToFormat: t => numberToFormat
      = "numberToFormat";
    let numberToFormat:
      (~value: float, ~format: string,
      ~roundingFunction: roundingFunction) => string;
    type stringToNumber = string => float;
    [@bs.get] external getStringToNumber: t => stringToNumber
      = "stringToNumber";
    let stringToNumber: string => float;
    type includes = (string, string) => bool;
    [@bs.get] external getIncludes: t => includes = "includes";
    let includes: (string, string) => bool;
    type insert = (string, string, int) => string;
    [@bs.get] external getInsert: t => insert = "insert";
    let insert: (string, string, int) => string;
    type multiplier = string => float;
    [@bs.get] external getMultiplier: t => multiplier = "multiplier";
    let multiplier: string => float;
    type correctionFactor1 = float => float;
    type correctionFactor2 = (float, float) => float;
    type correctionFactor3 = (float, float, float) => float;
    type correctionFactor4 = (float, float, float, float) => float;
    type correctionFactor5 = (float, float, float, float, float) => float;
    [@bs.get] external getCorrectionFactor1: t => correctionFactor1
      = "correctionFactor";
    [@bs.get] external getCorrectionFactor2: t => correctionFactor2
      = "correctionFactor";
    [@bs.get] external getCorrectionFactor3: t => correctionFactor3
      = "correctionFactor";
    [@bs.get] external getCorrectionFactor4: t => correctionFactor4
      = "correctionFactor";
    [@bs.get] external getCorrectionFactor5: t => correctionFactor5
      = "correctionFactor";
    let correctionFactor1: float => float;
    let correctionFactor2: (float, float) => float;
    let correctionFactor3: (float, float, float) => float;
    let correctionFactor4: (float, float, float, float) => float;
    let correctionFactor5: (float, float, float, float, float) => float;
    type toFixed = (float, int, roundingFunction, int) => float;
    [@bs.get] external getToFixed: t => toFixed = "toFixed";
    let toFixed: (float, int, roundingFunction, int) => float;
  };