// Developed by Daniil Bilohrudov on 15.05.2022
#include <cmath>
#include "Trapezoid.h"
const double EPS = 10e-5;

// check if points are in counter-clockwise order
bool ccw(const Point& a, const Point& b, const Point& c)
{
	return (c.y() - a.y()) * (b.x() - a.x()) > (b.y() - a.y()) * (c.x() - a.x());
}
bool compareDouble(double a, double b, double eps = EPS)
{
	return fabs(a - b) < eps;
}
bool Trapezoid::checkIfPossible(const Point& a, const Point& b, const Point& c, const Point& d)
{
	// check if segments are parallel by their slopes
	double slopeAB = (b.y() - a.y()) / (b.x() - a.x());
	double slopeBC = (c.y() - b.y()) / (c.x() - b.x());
	double slopeCD = (d.y() - c.y()) / (d.x() - c.x());
	double slopeAD = (a.y() - d.y()) / (a.x() - d.x());

	bool ABandCDparallel = compareDouble(slopeAB, slopeCD) || isinf(slopeAB - slopeCD); // check for inf for vertical lines
	bool BCandADparallel = compareDouble(slopeBC, slopeAD) || isinf(slopeBC - slopeAD);
	if (!(ABandCDparallel ^ BCandADparallel)) return false;

	// check if segments intersect
	bool intersect;
	if (BCandADparallel)
	{
		// check if two parallel lines aren't equal
		if (compareDouble(Segment(b, c).length(), Segment(a, d).length())) return false;
		// if AB and CD intersect
		intersect = ccw(a, c, d) != ccw(b, c, d) && ccw(a, b, c) != ccw(a, b, d);
	}
	else
	{
		// check if two parallel lines aren't equal
		if (compareDouble(Segment(a, b).length(), Segment(c, d).length())) return false;
		// if BC and AD intersect
		intersect = ccw(b, d, a) != ccw(c, d, a) && ccw(b, c, d) != ccw(b, c, a);
	}
	if (intersect) return false;

	_isABparallel = ABandCDparallel;
	return true;
}

// points should be in clockwise order
Trapezoid::Trapezoid(const Point& a, const Point& b, const Point& c, const Point& d) :
	_a(a), _b(b), _c(c), _d(d), _ab(nullptr), _bc(nullptr), _cd(nullptr), _ad(nullptr)
{
	if (!checkIfPossible(a, b, c, d)) throw BadTrapezoid("Trapezoid is impossible", a, b, c, d);
	return;
}

Trapezoid::Trapezoid(const Trapezoid& t) :
	_a(t._a), _b(t._b), _c(t._c), _d(t._d), _ab(nullptr), _bc(nullptr), _cd(nullptr), _ad(nullptr), _isABparallel(t._isABparallel)
{
	return;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& t)
{
	_a = t._a;
	_b = t._b;
	_c = t._c;
	_d = t._d;
	_ab = nullptr;
	_bc = nullptr;
	_cd = nullptr;
	_ad = nullptr;
	_isABparallel = t._isABparallel;
	return *this;
}

Trapezoid::~Trapezoid()
{
	delete _ab;
	delete _bc;
	delete _cd;
	delete _ad;
	return;
}

void Trapezoid::setApexA(const Point& a)
{
	if (!checkIfPossible(a, _b, _c, _d)) throw BadTrapezoid("Point a ruins trapezoid", a, _b, _c, _d);
	_ab = nullptr;
	_bc = nullptr;
	_cd = nullptr;
	_ad = nullptr;
	_a = a;
}

void Trapezoid::setApexB(const Point& b)
{
	if (!checkIfPossible(_a, b, _c, _d)) throw BadTrapezoid("Point b ruins trapezoid", _a, b, _c, _d);
	_ab = nullptr;
	_bc = nullptr;
	_cd = nullptr;
	_ad = nullptr;
	_b = b;
}

void Trapezoid::setApexC(const Point& c)
{
	if (!checkIfPossible(_a, _b, c, _d)) throw BadTrapezoid("Point c ruins trapezoid", _a, _b, c, _d);
	_ab = nullptr;
	_bc = nullptr;
	_cd = nullptr;
	_ad = nullptr;
	_c = c;
}

void Trapezoid::setApexD(const Point& d)
{
	if (!checkIfPossible(_a, _b, _c, d)) throw BadTrapezoid("Point d ruins trapezoid", _a, _b, _c, d);
	_ab = nullptr;
	_bc = nullptr;
	_cd = nullptr;
	_ad = nullptr;
	_d = d;
}

const Trapezoid::Segment& Trapezoid::sideAB() const
{
	if (_ab == nullptr)
		_ab = new Segment(_a, _b);
	return *_ab;
}

const Trapezoid::Segment& Trapezoid::sideBC() const
{
	if (_bc == nullptr)
		_bc = new Segment(_b, _c);
	return *_bc;
}

const Trapezoid::Segment& Trapezoid::sideCD() const
{
	if (_cd == nullptr)
		_cd = new Segment(_c, _d);
	return *_cd;
}

const Trapezoid::Segment& Trapezoid::sideAD() const
{
	if (_ad == nullptr)
		_ad = new Segment(_a, _d);
	return *_ad;
}

Trapezoid::Segment& Trapezoid::sideAB()
{
	if (_ab == nullptr)
		_ab = new Segment(_a, _b);
	return *_ab;
}

Trapezoid::Segment& Trapezoid::sideBC()
{
	if (_bc == nullptr)
		_bc = new Segment(_b, _c);
	return *_bc;
}

Trapezoid::Segment& Trapezoid::sideCD()
{
	if (_cd == nullptr)
		_cd = new Segment(_c, _d);
	return *_cd;
}

Trapezoid::Segment& Trapezoid::sideAD()
{
	if (_ad == nullptr)
		_ad = new Segment(_a, _d);
	return *_ad;
}

double Trapezoid::area() const
{
	double a, b, c, d;
	if (_isABparallel)
	{
		bool isABbigger = sideAB().length() > sideCD().length();
		a = isABbigger ? sideCD().length() : sideAB().length();
		b = isABbigger ? sideAB().length() : sideCD().length();
		c = sideBC().length();
		d = sideAD().length();
	}
	else
	{
		bool isADbigger = sideAD().length() > sideBC().length();
		a = isADbigger ? sideBC().length() : sideAD().length();
		b = isADbigger ? sideAD().length() : sideBC().length();
		c = sideAB().length();
		d = sideCD().length();
	}
	return ((a + b) / (4 * (b - a)) * sqrt((a + c + d - b) * (a + d - b - c) * (a + c - b - d) * (b + c + d - a)));
}

double Trapezoid::perimeter() const
{
	return sideAB().length() + sideBC().length() + sideCD().length() + sideAD().length();
}

ostream& operator<<(ostream& os, const Trapezoid& t)
{
	os << '/' << t.apexA() << ", " << t.apexB() << ", " << t.apexC() << ", " << t.apexD() << '\\';
	return os;
}

bool operator==(const Trapezoid& a, const Trapezoid& b)
{
	return compareDouble(a.area(), b.area());
}
bool operator!=(const Trapezoid& a, const Trapezoid& b)
{
	return !(a == b);
}

double Trapezoid::Segment::length() const
{
	return sqrt(pow(end().x() - start().x(), 2) + pow(end().y() - start().y(), 2));
}
double Trapezoid::Segment::distance(const Point& x) const
{
	Segment a(x, start());
	Segment b(x, end());

	double alen = a.length();
	double blen = b.length();
	double clen = length();

	double alpha1 = alen * alen + clen * clen - blen * blen;
	double alpha2 = blen * blen + clen * clen - alen * alen;

	if (alpha1 <= 0 || alpha2 <= 0)
		return min(alen, blen);

	double p = (alen + blen + clen) / 2.;
	return (2 * sqrt(p * (p - alen) * (p - blen) * (p - clen))) / clen;
}
const Point& Trapezoid::Segment::center() const
{
	delete _center;
	_center = 0;
	_center = new Point((start().x() + end().x()) / 2., (start().y() + end().y()) / 2.);
	return *_center;
}

ostream& operator<<(ostream& os, const Trapezoid::Segment& s)
{
	os << '[' << s.start() << ", " << s.end() << ']';
	return os;
}

void Trapezoid::BadTrapezoid::diagnose()
{
	cout << _reason << ": [" << _a << ", " << _b << ", " << _c << ", " << _d << "]" << endl;
}
