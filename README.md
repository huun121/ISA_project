# Čtečka novinek ve formátu Atom a RSS s podporou TLS
### Projekt do předmětu ISA 2022 <BR>VUT FIT v Brně
Program, který vypisuje informace uvedené ve stažených zdrojích (feed) ve formátu Atom a RSS 2.0. Program po spuštění stáhne zadané zdroje a na standardní výstup vypíše informace požadované uživatelem (např. názvy článků).

**POZOR: v rámci běhu programu vytváří dočasný soubor "_tmp.feedreader"**

#### Autor: Pavel Hurdálek (xhurda01)

#### Datum vytvoření: 30.10.2022

## Platforma:
* Linux

## Soubory:
* atom_parser.c
* atom_parser.h
* error_handling.h
* feedreader_tester.c
* feedreader_tester.h
* feedreader.c
* feedreader.h
* makefile
* README.md - základní informace o projektu
* manual.pdf - manuál
* rss_parser.c
* rss_parser.h
* ssl.c
* ssl.h

### Instalace:

* Ve složce se soubory zadejte příkaz: make
* Reinstalace také pouze pomocí příkazu: make
* Testy spustíte pomocí příkazu: make test


### Použití:
```
./feedreader <URL | -f <feedfile>> [-c <certfile>] [-C <certaddr>] [-T] [-a] [-u]
./feedreader <-h | --help>
```
Parametry (nezáleží na pořadí):
- URL -> Url adresa zdroje
- -f \<feedfile\> -> název souboru s url adresami zdrojů
- -c \<certfile\> -> soubor s certifikáty pro ověření platnosti certifikátu SSL/TLS
- -C \<certaddr\> -> adresář, ve kterém se mají vyhledávat certifikáty (SSL/TLS)
- -T -> pro každý záznam zobrazí navíc informace o čase změny záznamu
- -a -> pro každý záznam zobrazí jméno autora, či jeho e-mailová adresa
- -u -> pro každý záznam zobrazí asociované URL
- -h | --help -> výpis nápovědy

#### Příklad spuštění:
```
./feedreader https://what-if.xkcd.com/feed.atom -T

*** what if? ***
Transatlantic Car Rental
Aktualizace: 2022-09-06T00:00:00Z

Hailstones
Aktualizace: 2022-07-06T00:00:00Z

Hot Banana
Aktualizace: 2022-05-04T00:00:00Z

Earth-Moon Fire Pole
Aktualizace: 2018-05-21T00:00:00Z

Electrofishing for Whales
Aktualizace: 2017-03-09T00:00:00Z

```
#### Použitý kód:
* https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input

#### Zdroje:
1. https://www.rssboard.org/rss-specification
2. https://developer.ibm.com/tutorials/l-openssl/
3. https://wiki.openssl.org/index.php/SSL/TLS_Client
4. https://en.wikipedia.org/wiki/Atom_(web_standard)
2. Učební materiály do předmětu ISA FIT VUT 2022 v Brně
9. Linux manuál

