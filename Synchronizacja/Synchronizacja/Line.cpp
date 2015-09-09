#include "Line.h"

//konstruktor
CLine::CLine() : m_id(0), m_stops()
{}
//destruktor
CLine::~CLine()
{}
//lista przystankow linii
std::list<int> const& CLine::stopsList() const
{
	return m_stops;
}
//id lini
const int CLine::lineID() const
{
	return m_id;
}