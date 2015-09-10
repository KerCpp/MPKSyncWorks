#include "KnotNet.h"
#include "_slaves.h"

//konstruktor
CKnotNet::CKnotNet(const CconnectionMatrix &data)
{

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
bool CKnotNet::fill(const std::vector<int> &comb, const std::vector<int> &perm, int idKnot, const CconnectionMatrix &data, int period)
{
	if (!_isKnotEmpty(idKnot))
	{
		if (_badComb(comb))
			throw int(0);
		if (_badPerm(perm))
			throw int(1);
	}
	//else jesli pusty
	for each (const auto &stop in m_CStopList)
	{
		if (stop.id() == idKnot)
		{
			auto tTable = stop.setTTable();
			for (size_t i = 0; i < tTable.size(); i++)
			{
				if (tTable[i][0] == -1)
				{
					tTable[i].m_id = perm[i];
					tTable[i].m_startTime = comb[i];
					_expand(idKnot, perm[i],comb[i], data, period);
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
bool CKnotNet::_badComb(const std::vector<int>& cp, int id, bool perm = false) const
{
	int rawNum = 1;
	if (perm)
		rawNum = 0;
	///////////////
	for each (const auto &stop in m_CStopList)
	{
		if (stop.id() == id)
		{
			auto tTable = stop.setTTable();
			for (size_t i = 0; i < tTable.size() ; i++)
			{
				if (tTable[i][rawNum] != cp[i] && tTable[i][rawNum] != -1)
					return false;
			}
		}
	}
	return true;
}
//sprawdz czy dopisywana permutacja jest zgodna z tym co w wezle
bool CKnotNet::_badPerm(const std::vector<int>& perm, int id) const
{
	return _badComb(perm, id, true);
}
//wpisuje odpowiednie wartosci w calym ukladzie 
void CKnotNet::_expand(int knotId, int line, int time, const CconnectionMatrix &data, int period)
{
	const auto & lineInfo = data.whereLineStops(line);
	std::vector<ls> knotList = {};//ls jako ks= knot start(linia znana)
	int transferTime = 0;
	int actual = 0;
	for (size_t i = 0; i < lineInfo.size(); i++)
	{
		if (i != 0)
			transferTime += data.transferTime(i - 1, i);
		if (data.getStopInfo(lineInfo[i]).isItKnot())
			knotList.push_back(ls(lineInfo[i], transferTime));
		if (lineInfo[i] == knotId)
			actual = knotList.size() - 1;
	}
	knotList[0][1] = knotList[actual][1] - time;//pozwoli zaczac od petli miast wezla w srodku
	for (size_t i = 1; i < knotList.size(); i++)
		knotList[i][1] += knotList[0][1];
	for each  (auto &knot in m_CStopList)
	{
		knot//add line time zgodnie z knotList, gfdzie sa czasy ktore jeszcze trzeba zrobic modulo takt
	}
}