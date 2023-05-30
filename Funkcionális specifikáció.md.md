# Funkcionális specifikáció
## 1. Vágyálomrendszer leírása
A mi projektunk egy olyan eszköz lenne, amely érzékelők és/vagy motor forgatásával képes lenne húzni a függönyt - mikrokontroller pedig egy Arduino Uno lenne. A projektünben a 2 motor fény illetve hőmérséklet hatására fog majd mozogni. Lehetőség adva lesz arra is, hogy a motorokat keypad segítségével manuálisan lehessen majd mozgatni előre megadott kombinációk alapján. 

## 2. Alkatrész lista:
- szerelőlap
- 2 db arduino uno
- 2 db egyenáramú motor
- 1 db H-hidas motor hajtómű
- 1 db fototranzisztor
- 1 db hőmérséklet érzékelő
- 4X4-es billentyűzet (keypad)
- jumper kábelek
- ellenállások

## 3. Használati esetek (működés)
- 2 motor fény és hőmérséklet hatására képes mozogni

- keypad segítségével lehet beaállítani a különböző állapotokat

- alapvetően üres állapotban van, a távirányítóval szükséges kezelni

1. 4 gomb van:

	- Az A gomb lenyomása után meg lehet adni neki egy n számot.

		- A csillag lenyomásával lementi azt a számot a távolság változóba.

		- A # lenyomásával pedig törli a változó értékét.

	- A B állatpot automatikus állapotba teszi.

		- Ha meghalad egy bizonyos fény és hőmérsékletmennyiséget akkor behúzza a függönyt.

		- Ha nem, akkor pedig ki. (És operátor van a 2 érték között)

	- A C gomb lenyomásával manuális állapotba állítjuk.

		- Olyankor a * lenyomásával be, a # lenyomásával kihúzza a függyönyt

	- A D gomb lenyomásával előzlsször a hőmérsékletlimitet állítjuk be, hogy mikortól húzza be a függyönyt.

		- Aztán a * egyszeri lenyomásával a fény értéket ugyan így.

		- A # minden esetben törli mindkét értéket.

## 4. Képernyőtervek (sematikus rajz és CAD tervrajz)
- Sematikus rajzok:
<img width="443" alt="Sematikus" src="https://github.com/utassydenis/Robotika_csapat7/assets/114164351/d2243061-57f6-44d8-9666-8367b4e1e0a4">
<img width="444" alt="Sematikus2" src="https://github.com/utassydenis/Robotika_csapat7/assets/114164351/6b0e806b-9fcf-4116-8a6e-b75084eef6f0">

- CAD tervrajz:
<img width="417" alt="CAD" src="https://github.com/utassydenis/Robotika_csapat7/assets/114164351/4a81738d-9550-4e78-aa51-a29e54c31b3e">

## 5. Forgatókönyvek (állapotátmenet gráf)
Jelölések:
- FK: függöny nincsen behúzva
- FB: függöny behúzva
- FBH: függöny behúzása
- FKH: függöny kihúzása
- AU: automatikus
- M: manuális
- HL: hőmérsékletlimit
- FE: fény érték
- SZ: szám
- TV: távolsági változó lementése
- FÉH: fény és hőmérséklet meghaladása után
 
Gomb lenyomások jelölése: 
- A: a gomb lenyomása
- B: a gomb lenyomása
- C: a gomb lenyomása
- D: a gomb lenyomása
- *: mentés
- #: törlés 


