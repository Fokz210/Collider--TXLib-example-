#include "MathVector.h"

MathVector::MathVector() :
	val({0, 0})
{
}

MathVector::MathVector(DPOINT inVal) :
	val(inVal)
{
}

MathVector::MathVector(double inx, double iny) :
	val({inx, iny})
{
}

MathVector::~MathVector()
{
}

double MathVector::x()
{
	return val.x;
}

void MathVector::x(double inX)
{
	val.x = inX;
}

double MathVector::y()
{
	return val.y;
}

void MathVector::y(double inY)
{
	val.y = inY;
}

double MathVector::l()
{
	return sqrt(sqr(val.x) + sqr(val.y));
}

double MathVector::a()
{
	return asin(val.y / val.x);
}

MathVector MathVector::norm()
{
	return MathVector(MathVector(val) / l());
}

void MathVector::setVal(POINT inval)
{
	val.x = inval.x;
	val.y = inval.y;
}

void MathVector::setVal(DPOINT inval)
{
	val = inval;
}

DPOINT MathVector::pointValue()
{
	return val;
}

MathVector MathVector::operator = (const MathVector &ina)
{
	if (&ina == this)
		return *this;
	return MathVector(this->val = ina.val);
}

const MathVector & operator + (const MathVector & v1)
{
	return MathVector(v1.val);
}

const MathVector operator - (const MathVector & v1)
{
	return MathVector(-v1.val.x, -v1.val.y);
}

const MathVector operator + (const MathVector & left, const MathVector & right)
{
	return MathVector( left.val.x + right.val.x, left.val.y + right.val.y );
}

const MathVector operator - (const MathVector & left, const MathVector & right)
{
	return MathVector(left.val.x - right.val.x, left.val.y - right.val.y );
}

const double operator * (const MathVector & left, const MathVector & right)
{
	return double(left.val.x * right.val.x + left.val.y * right.val.y);
}

const MathVector operator * (const MathVector & left, const double & right)
{
	return MathVector( left.val.x * right, left.val.y * right );
}

const MathVector operator / (const MathVector & left, const double & right)
{
	if (right) return MathVector( left.val.x / right, left.val.y / right );
	else return left;
}

std::ostream& operator << (std::ostream &s, const MathVector &v)
{
	s << '(' << v.val.x << ", " << v.val.y << ')';
	return s;
}

std::istream& operator >> (std::istream &s, MathVector &v)
{
	std::cout << "Insert vector.\nX:";
	std::cin >> v.val.x;
	std::cout << "Y:";
	std::cin >> v.val.y;
	std::cout << std::endl;
	return s;
}

double VectorsAngleCos(MathVector a, MathVector b)
{
	if (a.l() * b.l() != 0) return (a * b) / (a.l() * b.l());
	else return 0;
}

