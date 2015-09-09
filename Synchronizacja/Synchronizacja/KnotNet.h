#pragma once
#include "przystanek.h"
#include <limits>
class CKnotNet
{
	std::vector<std::vector<int> > m_graphKnotsConn = {};
	std::vector<CStop> m_CStopList = {};
	int m_rating = INT_MIN;
	bool m_fin = false;
public:
	CKnotNet();//musi czytac idki z data
	~CKnotNet();
	bool operator<(const CKnotNet &rhs);
	const int rating() const;
	bool isGood() const;//czy wszystkie warunki spelnione sa
	bool fill(const std::vector<int> &, const std::vector<int> &);//dodanie nowych lini
	bool isKnotGood(int id) const;//czy wezel wypelniony
	const CStop& retKnot(int) const;
private:
	void _evalFunc();//wystawia rateing
	bool _finished() const;//wszystko wypelnione
};

  