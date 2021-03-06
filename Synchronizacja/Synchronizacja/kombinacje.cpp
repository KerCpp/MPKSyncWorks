#include "kombinacje.h"
#include "permutacja.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
//Konstruktor
Ccombinations::Ccombinations(const int numOfLines, const int& beat, const int& maxodchyl, int minodstep)
{
	std::string fileName="./";
	fileName += std::to_string(numOfLines);
	fileName += "_";
	fileName += std::to_string(beat);
	fileName += "_";
	fileName += std::to_string(maxodchyl);
	fileName += "_";
	fileName += std::to_string(minodstep);
	fileName += ".comb";
	if (fileExist(fileName))
	{
		_read(fileName);
	}
	else
	{
		_regularDistribution(beat, numOfLines);
		m_possibleDeviations.resize(numOfLines + 1);//w ostatniej lini sa odchylki
		_countDeviations(maxodchyl);
		_add(numOfLines, beat, maxodchyl, minodstep);
		_addpermutations();
		_write(fileName);
		//_changeRepresentataion();
	}
}
//Destruktor
Ccombinations::~Ccombinations()//sprzatanie
{
	//for (auto i = 0u; i < m_possibleDeviations.size(); i++)
		//delete[] m_possibleDeviations[i];
}
//Funkcja wylicza rozk�ad r�wnomierny
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
	std::sort(tmp.begin(), tmp.end());//po co w zasadzie - nie pamietam
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
	//m_possibleDeviations[m_possibleDeviations.size()-1] = new int[delay * 2 + 1];//wartosci odchylen
	m_possibleDeviations[m_possibleDeviations.size() - 1].resize(delay * 2 + 1);//wartosci odchylen
	for (auto i = 0; i < delay * 2 + 1; i++)
		m_possibleDeviations[m_possibleDeviations.size() - 1][i] = i-delay;

	for (auto i=0u; i < m_possibleDeviations.size()-1; i++)
	{
		//m_possibleDeviations[i] = new int[delay * 2 + 1];
		m_possibleDeviations[i].resize(delay * 2 + 1);
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
		if (_spaceCtrl(toAdd, space) && _beatSizeCtrl(toAdd, beat))
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
		int  ctrl = 0;
		for each (auto &v in p.retPermTab())
		{
			if (ctrl++ != 0)
			{
				std::vector<int> goodV;
				for each (auto &elem in v)
					goodV.push_back(elem.m_value);
				m_setkombi.insert(goodV);
			}
		}
	}
}
//zwraca kombinacje
const SviComb Ccombinations::retComb()
{
	return m_setkombi;
}
/*/zmienia reprezentacje z rozkladu co ile na minutowy
void changeRepresentation(Ccombinations& comb)
{
	for (auto &comb : m_setkombi)
	{
		std::vector<int> result[20];
		std::partial_sum(comb.begin(), comb.end(), result);
		for (auto i = 0u; i < comb.size(); i++)
			comb[i] = result[i];
	}
}*/
void Ccombinations::_read(const std::string& fileName)
{
	std::ifstream FILE;
	FILE.open(fileName, std::ios::in | std::ios::binary);
	while (true)
	{
		std::vector<int> vect = {};
		int tmp = 0;
		char sign = 0;
		FILE >> sign;
		if (FILE.eof())
			break;
		while (sign != ')' && (sign == '(' || sign == ','))
		{
			FILE >> tmp;
			vect.push_back(tmp);
			FILE >> sign;
		}
		m_setkombi.insert(vect);
	}
	FILE.close();
}
void Ccombinations::_write(const std::string& fileName)
{
	std::ofstream FILE;
	FILE.open(fileName, std::ios::out | std::ios::binary);
	for (auto& comb : m_setkombi)
	{
		FILE << "(";
		for (auto i = 0u; i < comb.size(); i++)
		{
			if (i != 0)
				FILE << ",";
			FILE << comb[i];
		}
		FILE << ")";
	}
	FILE.close();
}