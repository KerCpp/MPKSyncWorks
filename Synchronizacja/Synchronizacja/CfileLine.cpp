#include "CfileLine.h"
#include <string>
#include <sstream> 

//wejscie
const std::istream& operator>>(std::istream& INPUT, CfileLine &omNomNom)
{
	std::stringstream ss1,ss2,ss3,ss4,ss5;//a bo blad jakis
	char tmp[128];
	INPUT.getline(tmp, 100, ';');
	ss1 << tmp;
 	ss1 >> omNomNom.m_lineId;
	INPUT.getline(tmp, 100, ';');
	ss2 << tmp;
	omNomNom.m_route = ss2.str();
	INPUT.getline(tmp, 100, ';');
	ss3 << tmp;
	ss3 >> omNomNom.m_stopId;
	INPUT.getline(tmp, 100, ';');
	ss4 << tmp;
	omNomNom.m_stopName = ss4.str();
	INPUT.getline(tmp, 100, '\n');
	ss5 << tmp;
	ss5 >> omNomNom.m_transferTime;
	return INPUT;
}
