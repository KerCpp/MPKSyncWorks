#include "individual.h"

//konstruktor
individual::individual() : m_lsVect()
{}
//rzutowanie z sieci CknotNet - uproszczenie sieci do startow z petli
individual::individual(const CKnotNet &Net, const CconnectionMatrix &data)
{
	//WYMAGA SKONCZONEGO KNOTNET
}
//destruktor
individual::~individual()
{}
//dopisanie innego osobnika - troche jak dodawanie stringow
individual individual::operator+=(const individual &rhs)
{
	for each  (const auto &elem in rhs.retGenom())
	{
		m_lsVect.push_back(elem);
	}
	return *this;
}
//zwraca genom
const std::vector<ls>& individual::retGenom() const
{
	return m_lsVect;
}
//sposob wypisywania genomu
std::ostream& operator<<(std::ostream& out, const individual& rhs)
{
	for each  (const auto &elem in rhs.retGenom())
	{
		out << elem.m_id << " : " << elem.m_startTime << "|";
	}
	return out;
}