#pragma once
#include "_kint.h"
#include "_func.h"
#include "_slaves.h"
#include <vector>
#include <algorithm>

/*
Klasa pozwala na tworzenie kolejnych permutacji zadanego ci¹gu ustalonego typu i wykonywaniu na nich zadanej funkcji.
Algorytm Johnsona-Trottera : http://www.cut-the-knot.org/Curriculum/Combinatorics/JohnsonTrotter.shtml
TYPE - TYPE musi posiadaæ metodê do sprawdzania a < b
FUNC - funkcja operujaca na kolejnych permutacjach
dopuszczalna d³ugoœæ ³añcucha znaków to 20
*/

template < typename TYPE, void(*FUNC)(std::vector<kint<TYPE> > v, int SIZE) >
class Cpermutation
{
	std::vector< std::vector<kint<TYPE> > > m_permutationTab = {};
	std::vector<kint<TYPE> > m_permutation = {};//tablica z permutracja
	/////////////////////////////////////////////////////////////////

	friend void FUNC(std::vector<TYPE>, int);//funkcja operujaca na permutacjach
	typedef unsigned long long int ullint;
	void _swap(const int &position1, const int &position2)
	{
		kint<TYPE> tmp = m_permutation[position1];
		m_permutation[position1] = m_permutation[position2];
		m_permutation[position2] = tmp;
	}
	void _transfer(const std::vector<TYPE> sequence, int size)//transport ciagu do permutacji
	{
		std::vector<TYPE> sequenceCopy = sequence;//kopiowanie
		sort(sequenceCopy.begin(), sequenceCopy.end(), sort<TYPE>);
		for (auto i = 0; i < size; i++)//przek³adanie do w³aœciwego kontenera
		{
			m_permutation[size - 1 - i].m_value = sequenceCopy.back();
			m_permutation[size - 1 - i].m_index = size - 1 - i;
			sequenceCopy.pop_back();
		}
	}
	void _check(const int &position, kint2<TYPE> &eMax)//sprawdza czy nowy eMax
	{
		int neighbour;//element obok w ciagu
		(m_permutation[position].m_direction == left) ? neighbour = position - 1 : neighbour = position + 1;//z czym porownac
		if (m_permutation[position].m_index > m_permutation[neighbour].m_index)//jesli neighbour jest mniejszy to porownaj z eMax
		{
			if (m_permutation[position].m_index > eMax.m_index)
			{
				eMax.m_index = m_permutation[position].m_index;
				eMax.m_value = m_permutation[position].m_value;
				eMax.m_direction = position;//który element w wektorze
			}
			if (m_permutation[position].m_value == m_permutation[neighbour].m_value)
				throw "ERR_SAME_VAL";
		}
	}
	inline void _directionChange(const int &position){ (m_permutation[position].m_direction == ) ? m_permutation[position].m_direction = right : m_permutation[position].m_direction = left; };
	inline ullint _factorial(ullint n) { return (n == 1 || n == 0) ? 1 : _factorial(n - 1) * n; }
	
public:
	Cpermutation(const std::vector<TYPE> &sequence, const int size, bool save = false)
	{
		m_permutation.resize(size);
		_transfer(sequence, size);
		FUNC(m_permutation, size);//m_permutation startowa
		for (ullint it = 0; it < _factorial(static_cast<ullint>(size)) - 1; it++)//wszystkie permutacje
		{
			kint2<TYPE> eMax;
			bool ctrl_bit = true;
			for (auto i = 0; i < size; i++)
			{
				if (!((i == 0 && m_permutation[i].m_direction == left) || (i == size - 1 && m_permutation[i].m_direction == right)))
					try{ _check(i, eMax); } //szukamy eMax

				catch(char*){ ctrl_bit = false; }
			}
			(m_permutation[eMax.m_direction/*position*/].m_direction == left) ? _swap(eMax.m_direction, eMax.m_direction - 1) : _swap(eMax.m_direction, eMax.m_direction + 1);//zamiana kolejnoœci w tablicy
			for (auto i = 0; i < size; i++)
			{
				if (m_permutation[i].m_index > eMax.m_index)
					_directionChange(i);
			}
			if (ctrl_bit)
				save ? m_permutationTab.pushback(m_permutation) : FUNC(m_permutation, size);
		}
	}
	~Cpermutation(){};
	const std::vector < vector<kint<TYPE> > > & retPermTab() const
	{
		return m_permutationTab();
	}
};
