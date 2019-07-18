# bs-numeral

These are ReasonML/Bucklescript bindings for [Numeral.js](http://numeraljs.com/).

![BS-Numeral code screenshot](/screenshot.svg)

## Why use *this* BS-Numeral?

There are a few other Numeral bindings already made, and it's easy to write an simple binding yourself if you only use a few of its functions. This aims to be a complete implemenation, however. To help ensure accuracy, it uses (mostly) the same tests as vanilla Numeral.js. The goal of this project is to provide a hassle-free replacement for people used to using Numeral in their JavaScript.

## Documentation

As with most ReasonML bindings, the interface files are mostly self-documenting. [You can view this project's interface here](/src/Numeral.rei).

Numeral uses several JS paradigms that don't translate to ReasonML smoothly, but this tries to make the transition as straightforward as possible.

Notable differences between this and vanilla Numeral.js:
- You create a numeral object with `Numeral.make`.
- The `Numeral` module only accepts floats. This is because once a number gets passed to the JavaScript side, it essentially becomes a float anyway. `Numeral` always returns values as floats.
- To use a string as input, use `Numeral.String`. The bindings for that module are almost the same as the base module, except that it accepts strings and returns `option`s. By keeping the two modules separate, we don't have to deal with `option` cases every time we use the module.
- BS-Numeral cannot recieve `Null` as input.
- Some functions are not bound because they're mostly irrelevant in ReasonML, such as `isNumeral`.
- Some functions that can take several optional inputs are split into multiple functions. For example: `numeral.format` has been turned into `Numeral.defaultFormat`, `Numeral.format`, and `Numeral.formatRound`.
- The math functions, `add`, `subtract`, etc., can take any type as input.
- The helper functions (`numeral._`) are available in `Numeral.Helpers`. They are not documented or tested by vanilla Numeral.js, so their bindings here are not well tested either. Some of them are mostly irrelevant in ReasonML anyway.

# Build
```
npm run build
```

# Watch

```
npm run watch
```

# Editor
If you use `vscode`, Press `Windows + Shift + B` it will build automatically