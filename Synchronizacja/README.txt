Kr�tki opis plik�w i klas:
_func - funkcje odpowiedzialne za jakie� konkretne czynno�ci jak grupowanie lini czy synchronizacja
_kint - wykorzystywane typy
_slaves - funkcje pomocnicze ogolnego zastosowania
Line - zawiera klase reprezentujaca linie tramwajaowa
przystanek - zawiera klas� reprezentuj�c� przystanek
mpolaczen - zawiera klas� zawierajaca dane wejsciowe, czasy przejazdow, siec polaczen, bazuje na grafie skierowanym i wektorach lini i przystankow
permutacja - wiadomo
kombinacje - wiadomo
grupa - klasa reprezentujaca zgrupowanie lini tramwajowych
KnotNet - ekstrakt z mpolaczen zawiera tylko wezly z nalozonymi przejazdami
individual - osobnik, w zasadzie uproszczenie KnotNet zawiera tylko czasy odjazdow z petli w takcie dla kazdejz linii

UWAGA: W programie s� wykorzystane p�tle for each(typ arg in kolekcja), s� one zdaje si� z poza standardu w razie problem�w powinno dzia�a�:
for(typ arg :kolekcja)