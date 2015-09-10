#pragma once
#include "przystanek.h"
#include "mpolaczen.h"
#include <limits>
class CKnotNet
{
	//std::vector<std::vector<int> > m_graphKnotsConn = {};nie potrzebne bo i tak czytam z data
	std::vector<CStop> m_CStopList = {};
	int m_rating = INT_MIN;
	bool m_fin = false;
public:
	CKnotNet(const CconnectionMatrix &data);//musi czytac idki z data
	~CKnotNet();
	bool operator<(const CKnotNet &rhs);
	const int rating() const;
	bool isGood() const;//czy wszystkie warunki spelnione sa
	bool fill(const std::vector<int> &, const std::vector<int> &, int, const CconnectionMatrix &, int);//dodanie nowych lini
	bool isKnotGood(int id) const;//czy wezel wypelniony
	const CStop& retKnot(int) const;
private:
	void _evalFunc();//wystawia rateing
	bool _finished();//wszystko wypelnione
	bool _isKnotEmpty(int) const;
	bool _badComb(const std::vector<int>&, int, bool=false) const;
	bool _badPerm(const std::vector<int>&, int) const;
	void _expand(int, int, int, const CconnectionMatrix&, int);
};

  