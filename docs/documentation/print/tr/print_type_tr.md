# ```print(type) -> <-``` nedir?

```print(type) -> <-``` FlaScript'in cikti fonksiyonudur.

```print(type)``` su turleri destekler:
  * 1 - string
  * 2 - string& (& = null || nil)
  * 3 - var[int]
  * 4 - int& (& = null || nil)
  * 5 - input (Yapim asamasinda)
  * 6 - last (Yapim asamasinda.)
  * 7 - func
  * 8 - dynamic
  * 9 - get[] (string, int, string&, int&, env)
  * 10 - newline
  * 11 - colorized
  * 12 - rcolorized vs.

## string& nedir?

```string&``` bos, null(ya da nil) ya da bos 'string' olarak tanimlanabilir.

## dynamic nedir?

```dynamic``` normalde guncellenebilir stringler icin kullanilir.

### Ornek:

```
main() -> main {
	print(dynamic) -> set[title] -> "Hello World, Terminal :)" <-
}
```

#### set nedir?

```set``` girilen string degeri ile degisken turunu ayarlar ve gosterir.

## newline nedir?

```newline``` yeni satir operatoru koyar.

### Ornek:

```
main() -> main {
  print(newline)
}
```

### Output:

``` ``` (Yeni satira gecer.)

## colorized nedir?

```colorized``` C++, Go ve FlaScript icin bir kutuphanedir.

* ![C++ icin Colorized](https://github.com/ferhatgec/colorized)
* ![Go icin Colorized](https://github.com/ferhatgec/gocolorized)
* Colorized FlaScript'in cekirdegine dahil edilmistir.

### Ornek:
```
main() -> main {
  print(colorized[:11, 33:]) -> "Hello FlaScript! (Sari)" <-
  print(string) -> "Hello World! (Beyaz)"
}
```

#### ```colorized[:aa, bb:]```
* aa = Yazi tipi (KALIN, ITALIK, INCE vs.)
* bb  = Yazi rengi.


## colorized ve rcolorized arasindaki farklar.

```colorized``` sadece girilen degeri renklendirerek yazdirirken, ```rcolorized``` reset rengi eklenmemisse tum yazilari renklendirir.

### Ornek:

```
main() -> main {
  print(colorized[:11, 33:]) -> "Hello FlaScript! (Sari)" <-
  print(string) -> "Hello World! (Beyaz)"
}
```

```
main() -> main {
  print(rcolorized[:11, 33:]) -> "Hello FlaScript! (Sari)" <-
  print(string) -> "Hello World! (Sari)"
}
```


### Diger kullanimi:
``` print(rcolorized[:11, 33:])```


## func nedir?

```func``` `function` (fonksiyon) anlamina gelir.

Fonksiyondan alinan geri dondurulebilir stringleri ya da integerleri yazdirir. (string& ve int& hata verir)

### Ornek:

```
func -> Test() {
	return var(string) -> Hello world! <-
}

main() -> main {
    print(func) -> Test() <-
}
```


### Cikti:
```Hello world!```


#### Kaynaklar:
* 1 - ![fprintf](https://github.com/ferhatgec/flascript/blob/master/test/fprintf.fls)
* 2 - ![fprintln](https://github.com/ferhatgec/flascript/blob/master/test/fprintln.fls)
* 3 - ![execout](https://github.com/ferhatgec/flascript/blob/master/test/execout.fls)
* 4 - ![print_string](https://github.com/ferhatgec/flascript/blob/master/test/print_string.fls)
* 5 - ![print](https://github.com/ferhatgec/flascript/blob/master/test/print.fls)
* 6 - ![Function](https://github.com/ferhatgec/flascript/blob/master/test/returnstr.fls)
* 7 - ![Colorized](https://github.com/ferhatgec/flascript/blob/master/test/print_colorized.fls)
* 8 - ![RColorized](https://github.com/ferhatgec/flascript/blob/master/test/print_rcolorized.fls)
