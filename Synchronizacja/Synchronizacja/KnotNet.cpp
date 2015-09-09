#include "KnotNet.h"

//konstruktor
CKnotNet::CKnotNet(){}
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

}
//zwraca wezel w ktorym mozna sobie grzebac o dnaym id
const CStop& CKnotNet::retKnot(int) const
{

}