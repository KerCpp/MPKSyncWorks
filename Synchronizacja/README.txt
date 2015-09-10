Krótki opis plików i klas:
_func - funkcje odpowiedzialne za jakieœ konkretne czynnoœci jak grupowanie lini czy synchronizacja
_kint - wykorzystywane typy
_slaves - funkcje pomocnicze ogolnego zastosowania
Line - zawiera klase reprezentujaca linie tramwajaowa
przystanek - zawiera klasê reprezentuj¹c¹ przystanek
mpolaczen - zawiera klasê zawierajaca dane wejsciowe, czasy przejazdow, siec polaczen, bazuje na grafie skierowanym i wektorach lini i przystankow
permutacja - wiadomo
kombinacje - wiadomo
grupa - klasa reprezentujaca zgrupowanie lini tramwajowych
KnotNet - ekstrakt z mpolaczen zawiera tylko wezly z nalozonymi przejazdami
individual - osobnik, w zasadzie uproszczenie KnotNet zawiera tylko czasy odjazdow z petli w takcie dla kazdejz linii

UWAGA: W programie s¹ wykorzystane pêtle for each(typ arg in kolekcja), s¹ one zdaje siê z poza standardu w razie problemów powinno dzia³aæ:
for(typ arg :kolekcja)