#include "_func.h"
#include "Line.h"
#include "przystanek.h"
#include "KnotNet.h"
#include "_slaves.h"
#include "kombinacje.h"
#include "permutacja.h"
#include <queue>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ctime>

//do porownan w sync kolejce
class GRKnotComp
{
	bool reverse;
public:
	GRKnotComp(const bool& revparam = false) : reverse(revparam) {}
	bool operator() (const CStop &lhs, const CStop &rhs) const
	{
		if (reverse) return (lhs.numOfLines()<rhs.numOfLines());
		else return (lhs.numOfLines()>rhs.numOfLines());
	}
}KnotComp;

//czy kombinacja jest niepoprawna z punktu widzenia algorytmu
bool badComb(const std::vector<int>& comb, const CconnectionMatrix& data)
{
	return false;
}


/*
Funkcja testowa
*/
void wyswietl(std::vector<kint<int> > v, int R)
{
	std::cout << std::endl;
	for (auto i = 0; i < R; i++)
	{
		std::cout << v[i].m_value;
	}
}
/*
Funkcja dziel¹ca zbiór na grupy o wspolnych przystankach 
*/
std::vector<Cgroup> divideIntoGroups(const CconnectionMatrix &matrix)
{
	std::vector<Cgroup> groups;
	bool ctrl;
	int rootId = 0;
	while (rootId < matrix.numOfLines())
	{
		groups.push_back(Cgroup(rootId, matrix));
		ctrl = true;
		while (ctrl && rootId < matrix.numOfLines())
		{
			int ctrlroot = rootId;
			for (unsigned int i = 0; i < groups.size(); i++)
			{
				if (onlyOnceRuleCtrl(rootId, groups[i].groupMembers()))//jesli jest skladowa jakiejs grupy
				{
					rootId++;
					break;
				}
			}
			if (ctrlroot == rootId)//jesli nie nalezy to stworz grupe z tym elementem
				ctrl = false;

		}
	}
	return groups;
}
//tu sie dzieje cala magia(rekurencji)
CKnotNet& syncMagic(const std::vector<CStop> &pq, const CconnectionMatrix &data, const Cgroup &group, CKnotNet &bestOption, CKnotNet thisOption, int version = 0)
{
	if (thisOption.isKnotFull(pq[version].id()))//wezel juz wypelniony z poprzednich
		return syncMagic(pq, data, group, bestOption, thisOption, version + 1);
	CKnotNet tmpOption(thisOption);
	const SviComb &combi = Ccombinations(pq[version].numOfLines(), data.period(), data.delay()).retComb();
	const std::vector<int> &lines = data.whichLineStopsHere(pq[version].id());
	Cpermutation<int,wyswietl> perm(lines, lines.size(),true);

	for(const auto &c : combi)
	{
		if (badComb(c,data)) continue;
		for(const auto &p : perm.retPermTab())
		{
			static int count;
			std::cout << count++ << "   ";
			bool fin = false;
			tmpOption = thisOption;
			try
			{//a moze takt w mpolaczen?
				std::vector<int> goodperm;
				for each (auto &elem in p)
					goodperm.push_back(elem.m_value);
				fin = tmpOption.fill(c,goodperm, pq[version].id(), data);//fin moze zmienic sie na true
			}
			catch (int err_id)
			{
				if (err_id == 0)
					break;
				if (err_id == 1)
					continue;
				if (err_id == 2)
				{
					tmpOption = thisOption;
					continue;
				}
				std::cerr << "ERR_UNEX_EXP_THROWN";
				std::cin.sync();
				std::cin.get();
				std::abort();
			}
			if (fin)
			{
				//std::cout << tmpOption.rating() << "     ";
				if (bestOption.rating() < tmpOption.rating())
					bestOption = tmpOption;
			}
			else
				syncMagic(pq, data, group, bestOption, tmpOption, version + 1);
		}
	}
	return bestOption;
}
//sync grupy
const individual groupSync(const CconnectionMatrix &data, const Cgroup &group)
{
	std::vector<CStop> pq = {};
	for each  (const auto &stop in group.whereLinesStops())//wypelnianie "kolejki"
	{
		const CStop &stopInfo = data.getStopInfo(stop);
		if (stopInfo.isItKnot())
		{

			pq.push_back(stopInfo);
		}
		else continue;
	}
	std::stable_sort(pq.begin(), pq.end(), KnotComp);
	CKnotNet bestOption(data);
	syncMagic(pq, data, group,bestOption,bestOption);
	return individual(bestOption,data);
}
//funkcja synchronizuj¹ca
const individual sync(const CconnectionMatrix &data, const std::vector<Cgroup> &groups)
{
	individual result;
	for (auto i = 0u; i < groups.size(); ++i)
	{
		auto group = groups[i];
		result += groupSync(data, group);
	}
	return result;
}

//DO POPRAWY funkcja zapisuj¹ca wynik do pliku wynikowego 
void save(const individual &Arg)
{
	std::ofstream resFile;
	std::string fileName = "./result";
	//fileName += /*+czas z ctime*/; DODAæ
	fileName += ".txt";
	resFile.open(fileName, std::ios::out, std::ios::trunc);
	resFile << Arg;
	resFile.close();
}