#include "KnotNet.h"
#include "_slaves.h"
#include <algorithm>
#include <numeric>

//konstruktor sieci opartej o wezly
CKnotNet::CKnotNet(const CconnectionMatrix &data) : m_fin(false), m_rating(INT_MIN)
{
	for (auto i = 0; i < data.numOfStops(); i++)
	{
		if (data.getStopInfo(i).isItKnot())
			m_CStopList.push_back(data.getStopInfo(i));
	}
}
//destruktor
CKnotNet::~CKnotNet(){}
//porownuje rating
bool CKnotNet::operator<(const CKnotNet &rhs)
{
	return m_rating < rhs.rating();
}
//zwraca ocene ukladu
const int CKnotNet::rating() const
{
	return m_rating;
}
//czy wszystkie warunki sa spelnione
bool CKnotNet::isGood() const
{
	for each (const auto &knot in m_CStopList)
	{
		if (!knot.isGood())
			return false;
	}
	//if (!_mijanka()) return false;
	return true;
}
//dodanie nowych lini do grafu, zwraca czy finished
bool CKnotNet::fill(const std::vector<int> &comb, const std::vector<int> &perm, int idKnot, const CconnectionMatrix &data)
{
	bool tested = false;
	if (!_isKnotEmpty(idKnot))
	{
		tested = true;
		auto test = _badPermComb(perm, comb, idKnot);
		switch (test)
		{
		case 0:
			throw int(0);
			break;
		case 1:
			throw int(1);
			break;
		default:
			break;
		}
	}
	//else jesli pusty lub dobry
	auto combC(comb);
	auto permC(perm);
	std::partial_sum(comb.begin(), comb.end(), combC.begin());
	if (tested) _cut(combC, permC, idKnot);
	for(auto &stop : m_CStopList)
	{
		if (stop.id() == idKnot)
		{
			auto &tTable = stop.setTTable();
			for (size_t i = 0; i < tTable.size(); i++)
			{
				if (tTable[i][0] == -1)
				{
					tTable[i].m_id = permC[i];
					tTable[i].m_startTime = combC[i];
					_expand(idKnot, perm[i],comb[i], data);
				}
			}
			std::sort(tTable.begin(), tTable.end(), [](const ls &arg1, const ls &arg2)->bool{return arg1.m_startTime < arg2.m_startTime; });
			break;
		}
	}
	if (!isGood())
		throw int(2);
	if (_finished())
		_evalFunc();
	return m_fin;
}
//czy wypelnianie zakonczone jest
bool CKnotNet::_finished() 
{
	for each (const auto &knot in m_CStopList)
	{
		for each (const auto &ls in knot.setTTable())
		{
			if (ls.m_id == -1)//jesli nie wszystkie linie sa juz uzupelnione
				return false;
		}
	}
	m_fin = true;
	return true;
}
//czy dany wezel juz jest wypelniony
bool CKnotNet::isKnotFull(int id) const
{
	for each (const auto &knot in m_CStopList)
	{
		if (knot.id()==id)
		{
			for each (const auto &ls in knot.setTTable())
			{
				if (ls.m_id == -1)//jesli nie wszystkie linie sa juz uzupelnione
					return false;
			}
			return true;
		}
	}
	return false;
}
//funkcja samooceny
void CKnotNet::_evalFunc()
{
	m_rating = 0;
	for each (const auto &stop in m_CStopList)
	{
		m_rating+=stop.rating();
	}
}
//zwraca wezel w ktorym mozna sobie grzebac o dnaym id
const CStop& CKnotNet::retKnot(int i) const
{
	return m_CStopList[i];
}
bool CKnotNet::_isKnotEmpty(int id) const
{
	for each (const auto &knot in m_CStopList)
	{
		if (knot.id() == id)
		{
			for each (const auto &ls in knot.setTTable())
			{
				if (ls.m_id != -1)//jesli nie wszystkie linie sa juz uzupelnione
					return false;
			}
			return true;
		}
	}
	return false;
}
//sprawdz czy dopisywana permutacja/combinacja jest zgodna z tym co w wezle
short int CKnotNet::_badPermComb(const std::vector<int>& perm, const std::vector<int>& comb, int id) const
{
	enum badThings{badComb, badPerm, Good};
		int rawNum = 0;
		for (const auto &stop : m_CStopList)
		{
			if (stop.id() == id)
			{
				auto tTable = stop.setTTable();
				std::vector<int> combCopy(comb);
				std::partial_sum(comb.begin(), comb.end(), combCopy.begin());
				int opt = 0;
				for (size_t i = 0; i < tTable.size(); i++)
				{
					if (tTable[i][0] != -1)
					{
						auto tmp = opt;
						for (size_t j = opt; j < tTable.size(); j++)
						{
							if (perm[j] == tTable[i][0])
							{
								if (comb[j] == tTable[i][1])
								{
									opt = j + 1;
									break;
								}
								else
									return badComb;
							}
						}
						if (tmp == opt) return badPerm;
					}
				}
			}
		}
		return Good;//true
}
//przelicza i wpisuje odpowiednie wartosci w calym ukladzie 
void CKnotNet::_expand(int knotId, int line, int time, const CconnectionMatrix &data)
{
	const auto & lineInfo = data.whereLineStops(line);
	std::vector<ls> knotList = {};//ls jako ks= knot start(linia znana)
	int transferTime = 0;
	int actual = 0;

	for (auto i = 0u; i < lineInfo.size(); i++)//przeliczenie czasow na inne przystanki
	{
		if (i != 0)
			transferTime += data.transferTime(i - 1, i);
		if (data.getStopInfo(lineInfo[i]).isItKnot())
			knotList.push_back(ls(lineInfo[i], transferTime));
		if (lineInfo[i] == knotId)
			actual = knotList.size() - 1;
	}
	{
		auto minus = knotList[0][1];
		for (auto &k : knotList)
			k[1] -= minus;
	}
	knotList[0][1] = time - knotList[actual][1];//pozwoli zaczac od "petli" miast wezla w srodku
	knotList[0][1] = modulo(knotList[0][1], data.period());
	for (size_t i = 1; i < knotList.size(); i++)
		knotList[i][1] = modulo(knotList[i][1] + knotList[0][1], data.period());

	for (size_t i = 0; i < knotList.size(); i++)//wypelnianie wezlow
	{
		for (CStop &knot : m_CStopList)
		{
			if (knot.id() == knotList[i][0] && knot.id() != knotId)
			{
				auto &tTab = knot.setTTable();
				for (size_t j = 0; j < tTab.size(); j++)
				{
					if (tTab[j].m_startTime == -1)
					{
						tTab[j].m_id = line;
						tTab[j].m_startTime = knotList[i][1];
						std::sort(tTab.begin(), tTab.end(), [](const ls &arg1, const ls &arg2)->bool{return arg1.m_startTime < arg2.m_startTime; });
						break;
					}
				}
			}
		}
	}
}
//obcina dopisywane dane o to co juz jest w wezle
void CKnotNet::_cut(std::vector<int>& perm, std::vector<int>& comb, int id) const
{
	int rawNum = 0;
	for (const auto &stop : m_CStopList)
	{
		if (stop.id() == id)
		{
			auto tTable = stop.setTTable();
			for (size_t i = 0; i < tTable.size(); i++)
			{
				if (tTable[i][0] != -1)
				{
					for (size_t j = 0; j < tTable.size(); j++)
					{
						if (perm[j] == tTable[i][0])
						{
							perm[j] = -1;
							comb[j] = -1;
						}
					}
				}
			}
		}
	}
	__presort(comb, perm);
}