# Recursive Descent Parsing Demo using ReasonML

This was an exercise in the implementation of recursive descent parsing, written in ReasonML, for a small subset of the JSON standard.

The portion of the standard in question:

```
object
    {}
    { members }
members
    pair
    pair , members
pair
    string : value
value
    string
    object
```

You'll note that _arrays_ don't exist, and _value_ is one of _string_ or _object_. This restriction was put in place to reduce make the exercise practical.

## Execution

Install dependencies, then run `yarn run start`.

Output from the parser is displayed in the browser's console. Example:

```
Attempting to parse:  "hello"
String(hello)
Remainder:
Attempting to parse:  {"hello":"world"}
Object(Pair(hello => String(world)))
Remainder:
Attempting to parse:  {"a":"b","c":"d"}
Object(PairAndMembers(Pair(a => String(b)), Pair(c => String(d))))
Remainder:
Attempting to parse:  {"a":{"b":"c"}}
Object(Pair(a => Object(Pair(b => String(c)))))
Remainder:
```

## Credits

This project was bootstrapped with [Create React App](https://github.com/facebookincubator/create-react-app).