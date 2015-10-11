#include "KnotNet.h"
#include "_slaves.h"
#include <algorithm>

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
	return true;
}
//dodanie nowych lini do grafu, zwraca czy finished
bool CKnotNet::fill(const std::vector<int> &comb, const std::vector<int> &perm, int idKnot, const CconnectionMatrix &data)
{
	if (!_isKnotEmpty(idKnot))
	{
		if (_badComb(comb,idKnot, data))//blad logiczny
			throw int(0);
		if (_badPerm(perm,idKnot, data))
			throw int(1);
	}
	//else jesli pusty lub dobry
	for(auto &stop : m_CStopList)
	{
		if (stop.id() == idKnot)
		{
			auto &tTable = stop.setTTable();

			for (size_t i = 0; i < tTable.size(); i++)
			{
				if (tTable[i][0] == -1)
				{
					tTable[i].m_id = perm[i];
					tTable[i].m_startTime = comb[i];
					_expand(idKnot, perm[i],comb[i], data);//blad logiczny
				}
			}
			break;
		}
	}

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
bool CKnotNet::isKnotGood(int id) const
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
//sprawdz czy dopisywana kombinacja jest zgodna z tym co w wezle
bool CKnotNet::_badComb(const std::vector<int>& comb, int id, const CconnectionMatrix &data) const
{
	int rawNum = 1;
	///////////////
	for(const auto &stop : m_CStopList)
	{
		if (stop.id() == id)
		{
			auto tTable = stop.setTTable();
			auto tTCopy(tTable);
			auto combCopy(comb);
			auto itC = combCopy.end();
			auto itT= tTCopy.end();
			for (auto i = combCopy.size()-1; i > 0; i--)
			{
				//przetworzenie na czas wzgledem minuty 0
			}
		}
	} 
		return true;
}
//sprawdz czy dopisywana permutacja jest zgodna z tym co w wezle
bool CKnotNet::_badPerm(const std::vector<int>& perm, int id, const CconnectionMatrix &data) const
{
	{
		int rawNum = 0;
		for each (const auto &stop in m_CStopList)
		{
			if (stop.id() == id)
			{
				auto tTable = stop.setTTable();
				for (size_t i = 0; i < tTable.size(); i++)
				{
					if (tTable[i][rawNum] != perm[i] && tTable[i][rawNum] != -1)
						return false;
				}
			}
		}
		return true;
	}
}
//wpisuje odpowiednie wartosci w calym ukladzie 
void CKnotNet::_expand(int knotId, int line, int time, const CconnectionMatrix &data)
{
	const auto & lineInfo = data.whereLineStops(line);
	std::vector<ls> knotList = {};//ls jako ks= knot start(linia znana)
	int transferTime = 0;
	int actual = 0;
	for (auto i = 0u; i < lineInfo.size(); i++)
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
						// czy sortowac teraz czy moze na samym koncu?
						std::sort(tTab.begin(), tTab.end(), [](const ls &arg1, const ls &arg2)->bool{return arg1.m_startTime < arg2.m_startTime; });
						for (auto k = tTab.size()-1; k > 0; k++)
						{
							if (tTab[k - 1].m_startTime != -1)
								tTab[k].m_startTime -= tTab[k - 1].m_startTime;
						}
						break;
					}
				}
			}
		}
	}
}