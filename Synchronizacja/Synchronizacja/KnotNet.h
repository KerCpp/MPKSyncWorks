#pragma once
#include "przystanek.h"
#include <limits>
class CKnotNet
{
	std::vector<std::vector<CStop> > m_graphKnotsConn = {};
	int m_rating = INT_MIN;
public:
	CKnotNet();//musi czytac idki z data
	~CKnotNet();
	bool operator<(const CKnotNet &rhs);
	int rating() const;
	bool isGood() const;//czy wszystkie warunki spelnione sa
	void fill(const std::vector<int> &, const std::vector<int> &);//dodanie nowych lini
	bool finished() const;//wszystko wypelnione
	bool isKnotGood(int id);//czy wezel wypelniony
private:
	void _evalFunc();//wystawia rateing
};

