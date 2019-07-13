// Based on https://github.com/DefinitelyTyped/DefinitelyTyped/blob/master/types/numeral/index.d.ts

type numeralJSLocale = {
  delimiters: {
    .
    "thousands": string,
    "decimal": string,
  },
  abbreviations: {
    .
    "thousand": string,
    "million": string,
    "billion": string,
    "trillion": string,
  },
  ordinal: float => string,
  currency: {. "symbol": string},
};

type numeralJSOptions = {
  .
  currentLocale: string,
  zeroFormat: string,
  nullFormat: string,
  defaultFormat: string,
  scalePercentBy100: bool,
};

type roundingFunction = float => float;

// http://numeraljs.com/#custom-formats
type numeralJsFormat = {
  /* regexps: {
     	format: RegExp,
     	unformat: RegExp,
     }, */
  format: (string, roundingFunction) => string,
  unformat: string => float,
};

type registerType =
  | Format
  | Locale;

// http://numeraljs.com/#use-it
type numeral = {
  .
  // float=> numeral,
  "version": string,
  "isNumeral": bool,
  "options": numeralJSOptions,
  /**
	 * This function sets the current locale.  If no arguments are passed in,
	 * it will simply return the current global locale key.
	 */
  // [@bs.meth] "locale": (~key: string=?)=> string,
  /**
	 * This function provides access to the loaded locale data.  If
	 * no arguments are passed in, it will simply return the current
	 * global locale object.
	 *
	 * @param key Locale key, e.g 'es' for a spanish locale definition
	 */
  // [@bs.meth] "localeData": (~key: string=?)=> numeralJSLocale,
  /**
	 * Registers a language definition or a custom format definition.
	 *
	 * @param what Allowed values are: either 'format' or 'locale'
	 * @param key The key of the registerd type, e.g. 'de' for a german locale definition
	 * @param value The locale definition or the format definitiion
	 */
  [@bs.meth]
  "register": (registerType, string, numeralJSLocale) => numeralJSLocale,
  [@bs.meth]
  "register2": (registerType, string, numeralJsFormat) => numeralJsFormat,
  [@bs.meth] "zeroFormat": string => unit,
  [@bs.meth] "nullFormat": string => unit,
  [@bs.meth] "clone": unit => numeral,
  // [@bs.meth] "format": (~inputString:string=?, ~roundingFunction: roundingFunction=?)=> string,
  [@bs.meth] "format": unit => string,
  [@bs.meth] "unformat": string => float,
  [@bs.meth] "value": unit => float,
  [@bs.meth] "valueOf": unit => float,
  [@bs.meth] "set": float => numeral,
  [@bs.meth] "add": float => numeral,
  [@bs.meth] "subtract": float => numeral,
  [@bs.meth] "multiply": float => numeral,
  [@bs.meth] "divide": float => numeral,
  [@bs.meth] "difference": float => float,
  /*validate:(value: any, culture: any): boolean*/
};

type numeralString = {
  .
  // float=> numeral,
  "version": string,
  "isNumeral": bool,
  "options": numeralJSOptions,
  [@bs.meth]
  "register": (registerType, string, numeralJSLocale) => numeralJSLocale,
  [@bs.meth]
  "register2": (registerType, string, numeralJsFormat) => numeralJsFormat,
  [@bs.meth] "zeroFormat": string => unit,
  [@bs.meth] "nullFormat": string => unit,
  [@bs.meth] "clone": unit => numeral,
  // [@bs.meth] "format": (~inputString:string=?, ~roundingFunction: roundingFunction=?)=> string,
  [@bs.meth] "format": unit => string,
  [@bs.meth] "unformat": string => float,
  // DIFFERENT 
  [@bs.meth] "value": unit => Js.Nullable.t(float),
  [@bs.meth] "valueOf": unit => float,
  [@bs.meth] "set": float => numeral,
  [@bs.meth] "add": float => numeral,
  [@bs.meth] "subtract": float => numeral,
  [@bs.meth] "multiply": float => numeral,
  [@bs.meth] "divide": float => numeral,
  [@bs.meth] "difference": float => float,
  /*validate:(value: any, culture: any): boolean*/
};

type numeralConfig = {. [@bs.meth] "defaultFormat": string => unit};

[@bs.module] external numeral: float => numeral = "numeral";
[@bs.module] external numeralConfig: numeralConfig = "numeral";
[@bs.module] external numeralString: string => numeralString = "numeral";