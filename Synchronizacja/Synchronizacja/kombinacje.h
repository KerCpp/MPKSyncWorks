#pragma once
#include "_slaves.h"
#include <vector>
#include <set>
#include <iostream>

typedef std::set<std::vector<int>, vecComp> SviComb;

//klasa generujaca wszystkie dobre rozklady
class Ccombinations
{
	SviComb m_setkombi;
	std::vector<int*> m_possibleDeviations;
public:
	Ccombinations(const int, const int&, const int&, int = 1);
	~Ccombinations();//sprzatanie
	void show()
	{
		for (std::vector<int> var : m_setkombi)
		{
			for (unsigned int i = 0; i < var.size(); i++)
				std::cout << var[i];
			std::cout << std::endl;
		}
	}
	const SviComb& retComb();
private:
	void _regularDistribution(int, const int&);//wylicza podstawow¹ kombinacjê która bêdzie przekszta³cana
	bool _spaceCtrl(std::vector<int>&, int);
	bool _beatSizeCtrl(std::vector<int>&, int);
	int _beatSize(std::vector<int> &) const;
	void _add(int,int,int,int);
	void _countDeviations(int);
	void _addpermutations(); 
};
