// Developed by Daniil Bilohrudov on 15.05.2022
#pragma once
#ifndef _TRAPEZOID_H_
#define _TRAPEZOID_H_
#include "Point.h"
using namespace std;
class Trapezoid
{
public:
	class Segment;
	class BadTrapezoid;

	Trapezoid(const Point& a = Point(0, 0), const Point& b = Point(1, 1),
			  const Point& c = Point(2, 1), const Point& d = Point(3, 0));
	Trapezoid(const Trapezoid&);
	Trapezoid& operator=(const Trapezoid&);
	~Trapezoid();

	const Point& apexA() const { return _a; }
	const Point& apexB() const { return _b; }
	const Point& apexC() const { return _c; }
	const Point& apexD() const { return _d; }
	void setApexA(const Point&);
	void setApexB(const Point&);
	void setApexC(const Point&);
	void setApexD(const Point&);

	const Segment& sideAB() const;
	const Segment& sideBC() const;
	const Segment& sideCD() const;
	const Segment& sideAD() const;
	Segment& sideAB();
	Segment& sideBC();
	Segment& sideCD();
	Segment& sideAD();

	double area() const;
	double perimeter() const;
private:
	bool checkIfPossible(const Point&, const Point&, const Point&, const Point&);
	bool _isABparallel; // if AB is parallel to CD

	Point _a, _b, _c, _d;
	mutable Segment* _ab, * _bc, * _cd, * _ad;
};
ostream& operator<<(ostream&, const Trapezoid&);
bool operator==(const Trapezoid& a, const Trapezoid& b);
bool operator!=(const Trapezoid& a, const Trapezoid& b);

class Trapezoid::Segment
{
public:
	Segment(const Point& x, const Point& y) : _x(x), _y(y), _center(nullptr) {}
	~Segment() { delete _center; }

	const Point& start() const { return _x; }
	const Point& end() const { return _y; }
	const Point& center() const;
	double length() const;
	double distance(const Point&) const;
private:
	mutable Point* _center;
	const Point& _x, & _y;
};
ostream& operator<<(ostream&, const Trapezoid::Segment&);

class Trapezoid::BadTrapezoid
{
public:
	BadTrapezoid(string reason, const Point& a, const Point& b, const Point& c, const Point& d) :
				 _reason(reason), _a(a), _b(b), _c(c), _d(d) {}
	~BadTrapezoid() {}
	void diagnose();
private:
	string _reason;
	Point _a; Point _b; Point _c; Point _d;
};
#endif
