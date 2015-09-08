#pragma once
/*
Typ odpowiedzialny za zwroty liczb w ustawieniu w trakcie dzia³ania algorytmu wyliczania permutacji.
*/
enum direction { left, right };

/*
Struktura rozszerzaj¹ca int
m_direction - kierunek
m_index - numer porz¹dkowy
m_value - wartoœæ
*/
template <typename TYPE>
struct kint
{
	bool m_direction = left;// 0 lewo 1 prawo
	int m_index = 0;
	TYPE m_value = 0;
};

/*
Struktura rozszerzaj¹ca int
m_direction - kierunek
m_index - numer porz¹dkowy
m_value - wartoœæ
*/

template <typename TYPE>
struct kint2
{
	int m_direction = left;// 0 lewo 1 prawo
	int m_index = 0;
	TYPE m_value = 0;
};
