# FlaScript'te Hello World! yazdirmak.

## ```main() -> main``` nedir?

```main() -> main``` Bu kod blogu FlaScript yorumlayicisi icin bir bastlatma sinyali olusturur, tum kodlar buradan calisir.

### Ornek:
```
main() -> main {
  /> Kodunu buraya yazacaksin. </
}
```

## Hello World! yazdirmak.

Oncelikle, FlaScript ~3 farkli cikis opsiyonuna sahiptir.

* 1 - print
* 2 - fprintf || fprintln
* 3 - execout

### 1 - ```print```

```print``` varsayilan ve basit cikis komutudur. Bu kod C++ kodunu yurutur.

#### Ornek:
```
main() -> main {
  print(string) -> "Hello World!"
}
```

#### Cikti:
```Hello World!```

#### Ornek 2:
```
main() -> main {
  print(string) -> "Hello World!"
  print(newline)
}
```

#### Cikti:
```Hello World!``` (Yeni satira gecer)

```print``` bu turleri destekler:

* 1 - string
* 2 - string& (& = null || nil)
* 3 - var[int]
* 4 - int& (& = null || nil)
* 5 - input (Yapim asamasinda)
* 6 - last (Yapim asamasinda)
* 7 - func
* 8 - dynamic
* 9 - get[] (string, int, string&, int&, env)
* 10 - newline
* 11 - colorized
* 12 - rcolorized vs.

Bunlar, 'print' klasorunde olacak. Bekleyin!

### 2 - ```fprintf``` || ```fprintln```

```fprintf```, ```print``` den farklidir.. Coklu ciktiyi destekler.

```fprintln```, ```fprintf``` ile aynidir fakat son satira yeni satiri yazdirir.

#### Ornek:
```
main() -> main {
  fprintf(<%string>[:"Hello ":, :"FlaScript!":, :" 1234567890":])
}
```

#### Cikti:
```Hello FlaScript! 1234567890```

#### Ornek 2:
```
main() -> main {
  fprintln(<%string>[:"Hello ":, :"FlaScript!":, :" 1234567890":])
}
```

#### Cikti:
```Hello FlaScript! 1234567890``` (Yeni satira gecer)

```fprintf``` ve ```fprintln``` sadece ```string``` turunu destekler.

### 3 - ```execout```

```execout`` ExecutePlusPlus kutuphanesini taban alir ve bu komut girilmis komutun ciktisini yazdirir.

#### Ornek:
```
main() -> main {
	execout(-> echo Hello World! <-)
}
```

#### Cikti:
```Hello World!``` (Yeni satira gecer)

* Tip:
```execout(-> Komutlarin buraya. <-)```


#### Kaynaklar:
* 1 - ![fprintf](https://github.com/ferhatgec/flascript/blob/master/test/fprintf.fls)
* 2 - ![fprintln](https://github.com/ferhatgec/flascript/blob/master/test/fprintln.fls)
* 3 - ![execout](https://github.com/ferhatgec/flascript/blob/master/test/execout.fls)
* 4 - ![print_string](https://github.com/ferhatgec/flascript/blob/master/test/print_string.fls)
* 5 - ![print](https://github.com/ferhatgec/flascript/blob/master/test/print.fls)


