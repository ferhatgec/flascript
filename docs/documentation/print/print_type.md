# What is the ```print(type) -> <-```

```print(type) -> <-``` is FlaScript's output function.

```print(type)``` supports these types:
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

## what is the string&?

```string&``` is a null(or nil), blank string. 

## What is the dynamic?

```dynamic``` is normally uses for updatable strings.

### Example:

```
main() -> main {
	print(dynamic) -> set[title] -> "Hello World, Terminal :)" <-
}
```

#### What is the set?

```set``` is sets variable type with inputted string and shows.

## what is the newline?

```newline``` is puts newline operator.

### Example:

```
main() -> main {
  print(newline)
}
```

### Output:

``` ``` (Newline)

## What is the colorized?

```colorized``` is a library for C++, FlaScript and Golang.

* ![Colorized for C++](https://github.com/ferhatgec/colorized)
* ![Colorized for Go](https://github.com/ferhatgec/gocolorized)
* Colorized is integrated on FlaScript's core.

### Example:
```
main() -> main {
  print(colorized[:11, 33:]) -> "Hello FlaScript! (Yellow)" <-
  print(string) -> "Hello World! (White)"
}
```

#### ```colorized[:aa, bb:]```
* aa = Text type (BOLD, ITALIC, THIN etc.)
* bb  = Text color.


## Differences between of the colorized and rcolorized.

```colorized``` only colorize inputted text, ```rcolorized``` colorize all text if not appended reset color.

### Example:

```
main() -> main {
  print(colorized[:11, 33:]) -> "Hello FlaScript! (Yellow)" <-
  print(string) -> "Hello World! (White)"
}
```

```
main() -> main {
  print(rcolorized[:11, 33:]) -> "Hello FlaScript! (Yellow)" <-
  print(string) -> "Hello World! (Yellow)"
}
```


### Other use:
``` print(rcolorized[:11, 33:])```


## What is the func?

```func``` meaning is `function`

Prints returnable strings or integers from functions (string& and int& gets error)

### Example:

```
func -> Test() {
	return var(string) -> Hello world! <-
}

main() -> main {
    print(func) -> Test() <-
}
```


### Output:
```Hello world!```



#### Sources:
* 1 - ![fprintf](https://github.com/ferhatgec/flascript/blob/master/test/fprintf.fls)
* 2 - ![fprintln](https://github.com/ferhatgec/flascript/blob/master/test/fprintln.fls)
* 3 - ![execout](https://github.com/ferhatgec/flascript/blob/master/test/execout.fls)
* 4 - ![print_string](https://github.com/ferhatgec/flascript/blob/master/test/print_string.fls)
* 5 - ![print](https://github.com/ferhatgec/flascript/blob/master/test/print.fls)
* 6 - ![Function](https://github.com/ferhatgec/flascript/blob/master/test/returnstr.fls)
* 7 - ![Colorized](https://github.com/ferhatgec/flascript/blob/master/test/print_colorized.fls)
* 8 - ![RColorized](https://github.com/ferhatgec/flascript/blob/master/test/print_rcolorized.fls)
