#pragma once
#include <cmath>
#include <iostream>
#include "TXLib.h"
#define sqr(a) (a * a)

struct DPOINT
{
	double x;
	double y;
};

class MathVector
{
public:
	MathVector();
	MathVector(DPOINT inVal);
	MathVector(double x, double y);
	~MathVector();
	MathVector Visualise(double x, double y, double k, COLORREF color, int thickness, const char * name);
	double x();
	void x(double inX);
	double y();
	void y(double inY);
	double l();
	double a();
	MathVector norm();
	void setVal(POINT inval);
	void setVal(DPOINT inval);
	DPOINT pointValue();
	MathVector operator=(const MathVector &a);
	friend const MathVector & operator + (const MathVector &v1);
	friend const MathVector operator - (const MathVector &v1);
	friend const MathVector operator + (const MathVector& left, const MathVector& right);
	friend const MathVector operator - (const MathVector& left, const MathVector& right);
	friend const double operator * (const MathVector& left, const MathVector& right);
	friend const MathVector operator * (const MathVector& left, const double& right);
	friend const MathVector operator / (const MathVector& left, const double& right);
	friend std::ostream& operator << (std::ostream &s, const MathVector &v);
	friend std::istream& operator >> (std::istream &s, MathVector &v);
	friend MathVector vis(MathVector a);

private:
	DPOINT val;
};

double VectorsAngleCos(MathVector a, MathVector b);

