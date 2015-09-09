#include "KnotNet.h"

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
//4 kluczowe metody
//czy wszystkie warunki sa spelnione
bool CKnotNet::isGood() const
{

}
//dodanie nowych lini do grafu, zwraca czy finished
bool CKnotNet::fill(const std::vector<int> &comb, const std::vector<int> &perm)
{

	_evalFunc();
}
//czy wypelnianie zakonczone jest
bool CKnotNet::_finished() const
{
	if (m_fin)
		return true;
	else
	{

	}
}
//czy dany wezel juz jest ok
bool CKnotNet::isKnotGood(int id) const
{

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