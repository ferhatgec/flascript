# Basics of Print

## What is the ```print(type) -> ....```?

```print(type) -> ...``` is FlaScript's default output function. This function executes C++ code.

## How to print string in FlaScript?

Basically, FlaScript supports lots of output option. ```print(string) -> "..."``` is one of them.

* 1 - ```print(string) -> "....."```
* 2 - ```fprintf(<%string>[:"...":, :"....":])```
* 3 - ```execout(-> echo ... <-)```

### 1 - ```print(string) -> "...."```

#### Example:

```
main() -> main {
  print(string) -> "Welcome to FlaScript!"
}
```

#### Output:

```Welcome to FlaScript!```


### 2 - ```fprintf(<%string>[:"...":, :"....":])```

#### Example:
```
main() -> main {
    fprintf(<%string>[:"Welcome ":, :"to ":, :"FlaScript!":])
}
```

#### Output:
```Welcome to FlaScript!```

### 3 - ```execout(-> echo ... <-)```

#### Example:

```
main() -> main {
	execout(-> Welcome to FlaScript! <-)
}
```

#### Output:

```Welcome to FlaScript!```



## How to print integer in FlaScript?

```print(var[int]) -> ... <-```

Only ```print(type) -> <-``` supports integer type.

### Example:

```
main() -> main {
  print(var[int]) -> 1234567890 <-
}
```

### Output:

```1234567890```
