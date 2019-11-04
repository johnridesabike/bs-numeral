[@bs.deriving abstract]
type makeOptions = {
  currentLocale: string,
  zeroFormat: string,
  nullFormat: string,
  defaultFormat: string,
  scalePercentBy100: bool,
};

[@bs.deriving abstract]
type makeDelimiters = {
  thousands: string,
  decimal: string,
};
[@bs.deriving abstract]
type makeAbbreviations = {
  thousand: string,
  million: string,
  billion: string,
  trillion: string,
};
[@bs.deriving abstract]
type makeCurrency = {symbol: string};
[@bs.deriving abstract]
type makeLocale = {
  delimiters: makeDelimiters,
  abbreviations: makeAbbreviations,
  ordinal: float => string,
  currency: makeCurrency,
};
[@bs.deriving abstract]
type makeRegExps = {
  format: Js.Re.t,
  unformat: Js.Re.t,
};
[@bs.deriving abstract]
type makeFormat = {
  regexps: makeRegExps,
  [@bs.as "format"]
  formatFn: (float, string, float => float) => string,
  [@bs.as "unformat"]
  unformatFn: string => float,
};
[@bs.deriving abstract]
type numeral = {
  version: string,
  options: makeOptions,
};
[@bs.module "numeral"] external numeral: numeral = "default";
[@bs.send] external reset: numeral => unit = "reset";
let registerLocale: (string, makeLocale) => makeLocale;
let registerFormat: (string, makeFormat) => makeFormat;
let locale: (~key: string) => string;
let localeData: (~key: string) => makeLocale;
let setZeroFormat: string => unit;
let setDefaultFormat: string => unit;
let validate: ('a, 'b) => bool;
type t;
[@bs.module "numeral"] external make: float => t = "default";
[@bs.module "numeral"] external fromNumeral: t => t = "default";
[@bs.module "numeral"] external fromInt: int => t = "default";
[@bs.send] external clone: t => t = "clone";
[@bs.send] external formatDefault: t => string = "format";
[@bs.send] external format: (t, string) => string = "format";
[@bs.send] external formatRound: (t, string, float => float) => string
  = "format";
let unformat: (t, string) => float;
let value: t => float;
[@bs.send] external set: (t, float) => t = "set";
[@bs.send] external add: (t, float) => t = "add";
[@bs.send] external subtract: (t, float) => t = "subtract";
[@bs.send] external multiply: (t, float) => t = "multiply";
[@bs.send] external divide: (t, float) => t = "divide";
let difference: (t, float) => float;
module String:
  {
    [@bs.module "numeral"] external numeral: numeral = "default";
    [@bs.send] external reset: numeral => unit = "reset";
    let registerLocale: (string, makeLocale) => makeLocale;
    let registerFormat: (string, makeFormat) => makeFormat;
    let locale: (~key: string) => string;
    let localeData: (~key: string) => makeLocale;
    let setZeroFormat: string => unit;
    let setDefaultFormat: string => unit;
    let validate: ('a, 'b) => bool;
    type t;
    [@bs.module "numeral"] external make: string => t = "default";
    [@bs.module "numeral"] external fromNumeral: t => t = "default";
    [@bs.send] external clone: t => t = "clone";
    [@bs.send] external formatDefault: t => string = "format";
    [@bs.send] external format: (t, string) => string = "format";
    [@bs.send] external formatRound: (t, string, float => float) => string
      = "format";
    let unformat: (t, string) => option(float);
    let value: t => option(float);
    [@bs.send] external set: (t, string) => t = "set";
    [@bs.send] external add: (t, string) => t = "add";
    [@bs.send] external subtract: (t, string) => t = "subtract";
    [@bs.send] external multiply: (t, string) => t = "multiply";
    [@bs.send] external divide: (t, string) => t = "divide";
    let difference: (t, string) => option(float);
  };
module Helpers:
  {
    type t;
    [@bs.get] external getHelpers: numeral => t = "_";
    type numberToFormat = (float, string, float => float) => string;
    [@bs.get] external getNumberToFormat: t => numberToFormat
      = "numberToFormat";
    let numberToFormat:
      (~value: float, ~format: string,
      ~roundingFunction: float => float) => string;
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
    type toFixed = (float, int, float => float, int) => float;
    [@bs.get] external getToFixed: t => toFixed = "toFixed";
    let toFixed: (float, int, float => float, int) => float;
  };