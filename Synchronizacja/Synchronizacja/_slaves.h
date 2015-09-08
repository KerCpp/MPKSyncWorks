#pragma once
#include <vector>
#include <set>

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

std::set<int> addToSet(std::vector<int>);
std::set<int> addToSet(std::set<int>);

bool onlyOnceRuleCtrl(const int &id, const std::vector<int> &vect);

//do porownan w sync kolejce
class GRKnotComp
{
	bool reverse;
public:
	GRKnotComp(const bool& revparam = false) : reverse(revparam) {}
	bool operator() (const CStop &lhs, const CStop &rhs) const
	{
		if (reverse) return (lhs.numOfLines()>rhs.numOfLines());
		else return (lhs.numOfLines()<rhs.numOfLines());
	}
}KnotComp;