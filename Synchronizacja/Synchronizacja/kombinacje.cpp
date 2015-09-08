#include "kombinacje.h"
#include "permutacja.h"
#include <algorithm>
#include <iostream>
//Konstruktor
Ccombinations::Ccombinations(const int numOfLines, const int beat, const int maxopoznienie, const int minodstep)
{
	_regularDistribution(beat, numOfLines);
	m_possibleDeviations.resize(numOfLines+1);//w ostatniej lini sa odchylki
	_countDeviations(maxopoznienie);
	_add(numOfLines, beat, maxopoznienie, minodstep);
	_addpermutations();
}
//Destruktor
Ccombinations::~Ccombinations()//sprzatanie
{
	for (auto i = 0u; i < m_possibleDeviations.size(); i++)
		delete[] m_possibleDeviations[i];
}
//Funkcja wylicza rozk³ad równomierny
void Ccombinations::_regularDistribution(int beat, const int &numOfLines)
{
	int i = 0;
	std::vector<int> tmp;
	tmp.resize(numOfLines);
	while (beat--!=0)
	{
		tmp[i]++;
		(i < numOfLines-1) ? i++ : i = 0;
	}
	std::sort(tmp.begin(), tmp.end());
	m_setkombi.insert(tmp);
}
//Funkcja liczy dluigosc taktu
int Ccombinations::_beatSize(std::vector<int> &komb) const
{
	int suma = 0;
	for each (auto i in komb)
		suma += i;
	return suma;
}
//Funkcja wylicza tablice odchylek
void Ccombinations::_countDeviations(int delay)
{
	m_possibleDeviations[m_possibleDeviations.size()-1] = new int[delay * 2 + 1];//wartosci odchylen
	for (auto i = 0; i < delay * 2 + 1; i++)
		m_possibleDeviations[m_possibleDeviations.size() - 1][i] = i-delay;

	for (auto i=0u; i < m_possibleDeviations.size()-1; i++)
	{
		m_possibleDeviations[i] = new int[delay * 2 + 1];
		for (auto j = 0; j < delay*2+1; j++)
			m_possibleDeviations[i][j] = std::max(0, (*m_setkombi.begin())[i])+m_possibleDeviations[m_possibleDeviations.size()-1][j];
	}
	m_possibleDeviations.pop_back();//usuniecie samych odchylek
}
//dodanie nowej kombinacji
void Ccombinations::_add(int numOfLines, int beat, int delay, int space)
{
	std::vector<int> toAdd;//wektor do dopisania
	toAdd.resize(numOfLines);
	std::vector<int> counter;//kontrola zakresu
	counter.resize(numOfLines+1);
	std::fill(counter.begin(), counter.end(), 0);

	while (counter.back() != 1)
	{
		for (auto i = 0; i < numOfLines; i++)//wpisywanie do wektora
			toAdd[i] = m_possibleDeviations[i][counter[i]];
		counter[0]++;
		for (auto i = 0; i < numOfLines; i++)//zwiekszaj tylko jesli poprzednik zrobil caly cykl
		{
			if (counter[i] == 2*delay+1)
			{
				counter[i + 1]++;
				counter[i] = 0;
			}

		}
		if (_spaceCtrl(toAdd, beat) && _beatSizeCtrl(toAdd, space))
		{
			std::sort(toAdd.begin(),toAdd.end());
			m_setkombi.insert(toAdd);
		}
	}
}
//Kontrola odstepow
bool Ccombinations::_spaceCtrl(std::vector<int>&v, int space)
{
	for (auto i = 0u; i < v.size(); i++)
	{
		if (space > v[i])
			return false;
	}
	return true;
}
//Kontrola dlugosci taktu
bool Ccombinations::_beatSizeCtrl(std::vector<int>&v, int beat)
{
	return (beat == _beatSize(v)) ? true : false;
}
//dodaje permutacje juz obliczonych kombinacji
void Ccombinations::_addpermutations()
{
	auto it = m_setkombi.begin();
	const size_t size = m_setkombi.size();
	for (size_t i = 0; i < size; i++)
	{
		Cpermutation<int, wyswietl> p((*it), (*it).size(), true);
		it++;
		for each (const auto &v in p.retPermTab())
		{
			m_setkombi.insert(v);
		}
	}
}
//zwraca kombinacje
const SviComb& Ccombinations::retComb()
{
	return m_setkombi;
}