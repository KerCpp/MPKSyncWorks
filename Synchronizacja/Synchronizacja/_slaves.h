#pragma once
#include <vector>
#include <set>
#include <iostream>
#include <string>

//klasa do porownan w zbiorze
struct vecComp
{
	bool operator()(const std::vector<int> &v1, const std::vector<int> &v2) const
	{
		unsigned int it = 0;
		while (it < v1.size())
		{
			if (v1[it] < v2[it]) return true;
			else if (v1[it] == v2[it]) it++;
			else break;
		}
		return false;
	}
};

template<typename TYP>
struct sort
{
	bool operator() (TYP i, TYP j) { return (i<j); }
};


struct sort2
{
	bool operator() (int i, int j) { return (i<j); }
};

//ostatecznie nie uzywane?
//std::set<int> addToSet(std::vector<int>); 
//std::set<int> addToSet(std::set<int>);

bool onlyOnceRuleCtrl(const int &id, const std::vector<int> &vect);

struct ls//line start
{
	int m_id = -1;
	int m_startTime = -1;
	ls() : m_id(-1), m_startTime(-1){}
	ls(int id, int time) : m_id(id), m_startTime(time) {}
	int& operator[](int i)
	{
		if (i == 0)
			return m_id;
		else if (i == 1)
			return m_startTime;
		else
		{
			std::cerr << "ERR_NO_MORE_ELEM";
			std::cin.sync();
			std::cin.get();
			abort();
		}
	}
};


struct CgraphKnot
{
	bool m_conj = false;
	int m_transferTime = 0;
};

int modulo(int, int);

struct Ctime
{
	int m_h;
	int m_m;
	int m_s;
	Ctime();
	Ctime(int h, int m, int s) : m_h(h), m_m(m), m_s(s){}
	int operator-(Ctime);//NIEBEZPIECZNE 
	friend const std::istream& operator>>(std::istream& INPUT, Ctime & OmNomNom);
};

class CidParser
{
public:
	int m_programId;
	std::string m_orgName;
	CidParser(int i, std::string s) : m_programId(i), m_orgName(s){}
};

void __presort(std::vector<int>& c, std::vector<int>& p);
bool fileExist(std::string&);

