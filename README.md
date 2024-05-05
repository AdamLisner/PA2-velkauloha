# FITExcel - Tabulkový procesor

FITExcel je tabulkový procesor vyvinutý jako součást projektu pro předmět na FIT VUT. Umí manipulovat s buňkami, vypočítávat hodnoty podle vzorců, detekovat cyklické závislosti a ukládat/načítat obsah tabulky.

## Obsah Repozitáře

- [**AST/**](AST/): Soubory pro abstraktní syntaktický strom.
- [**CMakeLists.txt**](CMakeLists.txt): Konfigurační soubor pro CMake.
- [**CPos.cpp, CPos.h**](CPos.cpp): Implementace pozice v tabulce.
- [**CSpreadsheet.cpp, CSpreadsheet.h**](CSpreadsheet.cpp): Implementace tabulkového procesoru.
- [**expression.h**](expression.h): Definice třídy Expression pro zpracování výrazů.
- [**hash_pair.h**](hash_pair.h): Definice hashovací funkce pro páry hodnot.
- [**README.md**](README.md): Informace o repozitáři.
- [**test.cpp**](test.cpp): Testy funkcí tabulkového procesoru.
- [**x86_64-linux-gnu/**](x86_64-linux-gnu/): Soubory pro konkrétní architekturu.
