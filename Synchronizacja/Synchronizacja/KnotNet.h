#pragma once
#include "przystanek.h"
#include "mpolaczen.h"
#include "_slaves.h"
class CKnotNet
{
	std::vector<CStop> m_CStopList;
	int m_rating = INT_MIN;
	bool m_fin = false;
	std::vector<loopLine> m_loops;
public:
	CKnotNet(const CconnectionMatrix &data);//musi czytac idki z data
	CKnotNet();
	~CKnotNet();
	bool operator<(const CKnotNet &rhs);
	const int rating() const;
	bool isGood(int,int) const;//czy wszystkie warunki spelnione sa
	bool fill(const std::vector<int> &, const std::vector<int> &, int, const CconnectionMatrix &);//dodanie nowych lini
	bool isKnotFull(int id) const;//czy wezel wypelniony
	const CStop& retKnot(int) const;
private:
	void _evalFunc();//wystawia rateing
	bool _finished();//wszystko wypelnione
	bool _isKnotEmpty(int) const;
	//bool _badComb(const std::vector<int>&, int, const CconnectionMatrix&) const;
	short int _badPermComb(const std::vector<int>&, const std::vector<int>&, int) const;
	void _expand(int, int, int, const CconnectionMatrix&);
	void _cut(std::vector<int>&, std::vector<int>&, int) const;
	bool _loopsGood(int) const;
	bool _negTestLoop(const loopLine&, int) const;
};

  