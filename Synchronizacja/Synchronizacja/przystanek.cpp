#include "przystanek.h"

//konstrukytor
CStop::CStop(){}
//destruktor
CStop::~CStop(){}
//czy jest petla
bool CStop::isItTerminus() const
{
	return m_terminus;
}
//czy jest wezlem
bool CStop::isItKnot() const
{
	return m_knot;
}
//ustaw wezel
void CStop::setKnot()
{
	m_knot = true;
}
//zlikwiduj wezel
void CStop::unsetKnot()
{
	m_knot = false;
}
//ustaw petle
void CStop::setTerminus()
{
	m_terminus = true;
}
//zniszcz petle 666 :D
void CStop::unsetTerminus()
{
	m_terminus = false;
}
//ilosc lini zatrzymujacyhc sie na przystanku
const int CStop::numOfLines() const
{
	return m_lines.size();
}
//id przystanku
const int CStop::id() const
{
	return m_id;
}
void nic(){}