# bs-numeral

These are ReasonML/Bucklescript bindings for [Numeral.js](http://numeraljs.com/).

![bs-numeral code screenshot](/screenshot.png)

## 🏁 Use in your project

Run this command in your project's directory:
```
npm i @johnridesabike/bs-numeral
```

And then add the project to the `bs-dependencies` array in your `bsconfig.json` file, like so:
```json
"bs-dependencies": [
    "@johnridesabike/bs-numeral"
]
```

## 🧐 Why use this bs-numeral?

There are a few other Numeral.js bindings, and it's easy to write an simple binding yourself if you only use a few of its functions. This project aims to be a complete implementation. To help ensure accuracy, it uses (mostly) the same tests as vanilla Numeral.js. The goal is to provide a hassle-free replacement for people used to using Numeral.js in their JavaScript.

## 📝 Documentation

As with most ReasonML bindings, the interface files are mostly self-documenting. [You can view this project's interface here](/src/Numeral.rei).

Numeral.js uses several JS paradigms that don't directly translate to ReasonML, but this tries to make the transition as smooth as possible.

Notable differences between this binding and vanilla Numeral.js:
- You create a numeral object with `Numeral.make`.
- The `Numeral` module only accepts floats. This is because once a number gets passed to the JavaScript side, it essentially becomes a float anyway. `Numeral` always returns values as floats.
- To use a string as input, use `Numeral.String`. The bindings for that module are almost the same as the base module, except that it accepts strings and returns `option`s. By keeping the two modules separate, we don't have to deal with `option` cases every time we use the module.
- bs-numeral cannot recieve `Null` as input.
- Some functions are not bound because they're irrelevant in ReasonML, such as `isNumeral`.
- Some functions that can take several optional inputs are split into multiple functions. For example: `numeral.format` has been turned into `Numeral.defaultFormat`, `Numeral.format`, and `Numeral.formatRound`.
- The math functions, `add`, `subtract`, etc., can only take floats (or strings, for the `String` module).
- The helper functions (`numeral._`) are available in `Numeral.Helpers`. They are not documented or tested by vanilla Numeral.js, so their bindings here are not well tested either. Some of them are irrelevant in ReasonML anyway.
- Numeral.js uses has several functions that accept or return JS objects for configuration. This binding uses BuckleScript abstract types as a replacement, which are rely on helper functions. For example, the confguration object is created with `makeConfig`, and the format configuration object is created with `makeFormat`. [The exact bindings are at the top of the rei file](/src/Numeral.rei).

You'll notice that this binding is very strict about what types are accepted as input. Numeral.js can throw a runtime error with malformed inputs, or simply return `null`. Strictness helps ensure that corrupt data doesn't escape into the rest of your code. If you find the strictness too limiting, open an issue with your situation.

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


## ✍️ Authors

- [@johnridesabike](https://github.com/johnridesabike) - Idea and initial work