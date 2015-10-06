#include "Line.h"

//lista przystankow linii
std::list<ls> const& CLine::stopsList() const
{
	return m_stops;
}
//id lini
const int CLine::lineID() const
{
	return m_id;
}
//lista przystankow linii
std::list<ls> & CLine::stopsList() 
{
	return m_stops;
}
