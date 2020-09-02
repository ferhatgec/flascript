# Print'in temelleri.

## ```print(type) -> ....``` nedir?

```print(type) -> ...``` FlaScript'in varsayilan cikis fonksiyonudur. Bu fonksiyon C++ kodunu yurutur.

## FlaScript'te nasil 'string' yazdirabilirim? 

Basitce, FlaScript bircok cikti turunu destekler. ```print(string) -> "..."``` bunlardan birisidir.

* 1 - ```print(string) -> "....."```
* 2 - ```fprintf(<%string>[:"...":, :"....":])```
* 3 - ```execout(-> echo ... <-)```

### 1 - ```print(string) -> "...."```

#### Ornek:

```
main() -> main {
  print(string) -> "Welcome to FlaScript!"
}
```

#### Cikti:

```Welcome to FlaScript!```


### 2 - ```fprintf(<%string>[:"...":, :"....":])```

#### Ornek:
```
main() -> main {
    fprintf(<%string>[:"Welcome ":, :"to ":, :"FlaScript!":])
}
```

#### Cikti:
```Welcome to FlaScript!```

### 3 - ```execout(-> echo ... <-)```

#### Ornek:

```
main() -> main {
	execout(-> Welcome to FlaScript! <-)
}
```

#### Cikti:

```Welcome to FlaScript!```


## FlaScript'te nasil 'integer' degeri yazdirabilirim? 

```print(var[int]) -> ... <-```

Sadece ```print(type) -> <-``` 'integer' (tamsayi) turunu destekler.

### Ornek:

```
main() -> main {
  print(var[int]) -> 1234567890 <-)
}
```

### Cikti:

```1234567890```
