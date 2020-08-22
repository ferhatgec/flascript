# Write Hello World! in FlaScript.

## What is the ```main() -> main```?

```main() -> main``` This code block is make a start signal from FlaScript interpreter, all codes working from here.

### Example:
```
main() -> main {
  /> Your code here. </
}
```

## Write Hello World!

First, FlaScript has ~3 different output option.

* 1 - print
* 2 - fprintf || fprintln
* 3 - execout

### 1 - ```print```

```print``` is default and simply output command. This is executes C++ code.

#### Example:
```
main() -> main {
  print(string) -> "Hello World!"
}
```

#### Output:
```Hello World!```

#### Example 2:
```
main() -> main {
  print(string) -> "Hello World!"
  print(newline)
}
```

#### Output:
```Hello World!``` (newline)

```print``` supports these types. 

* 1 - string
* 2 - string& (& = null || nil)
* 3 - var[int]
* 4 - int& (& = null || nil)
* 5 - input (Under the construction)
* 6 - last (Under the construction)
* 7 - func
* 8 - dynamic
* 9 - get[] (string, int, string&, int&, env)
* 10 - newline
* 11 - colorized
* 12 - rcolorized etc.

These, will be in the 'print' folder. Wait up.

### 2 - ```fprintf``` || ```fprintln```

```fprintf``` is different than ```print```. Supports multiple text.

```fprintln``` same with ```fprintf``` but prints newline into last line.

#### Example:
```
main() -> main {
  fprintf(<%string>[:"Hello ":, :"FlaScript!":, :" 1234567890":])
}
```

#### Output:
```Hello FlaScript! 1234567890```

#### Example 2:
```
main() -> main {
  fprintln(<%string>[:"Hello ":, :"FlaScript!":, :" 1234567890":])
}
```

#### Output:
```Hello FlaScript! 1234567890``` (newline)

```fprintf``` and ```fprintln``` supports only ```string``` type.

### 3 - ```execout```

```execout`` is based on ExecutePlusPlus library and this command is gets inputted command's output.

#### Example:
```
main() -> main {
	execout(-> echo Hello World! <-)
}
```

#### Output:
```Hello World!``` (newline)

* Tip:
```execout(-> your command here <-)```


#### Sources:
* 1 - ![fprintf](https://github.com/ferhatgec/flascript/blob/master/test/fprintf.fls)
* 2 - ![fprintln](https://github.com/ferhatgec/flascript/blob/master/test/fprintln.fls)
* 3 - ![execout](https://github.com/ferhatgec/flascript/blob/master/test/execout.fls)
* 4 - ![print_string](https://github.com/ferhatgec/flascript/blob/master/test/print_string.fls)
* 5 - ![print](https://github.com/ferhatgec/flascript/blob/master/test/print.fls)


