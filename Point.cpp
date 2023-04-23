// Developed by Daniil Bilohrudov on 15.05.2022
#include "Point.h"
#include <iostream>
using std::cout;
using std::endl;

Point& Point::operator=(const Point& p)
{
	_x = p._x;
	_y = p._y;
	return *this;
}

Point::Point(const double x, const double y) : _x(x), _y(y)
{
	return;
}

Point::Point(const Point& p) : _x(p._x), _y(p._y)
{
	return;
}

Point::~Point()
{
	return;
}

ostream& operator<<(ostream& os, const Point& p)
{
	os << "(" << p.x() << ", " << p.y() << ")";
	return os;
}

const Point operator+(const Point& u, const Point& v)
{
	return Point(u.x() + v.x(), u.y() + v.y());
}

Point& operator+=(Point& u, const Point& v)
{
	u.x() += v.x();
	u.y() += v.y();
	return u;
}

bool operator==(const Point& u, const Point& v)
{
	return (u.x() == v.x() && u.y() == v.y());
}

bool operator!=(const Point& u, const Point& v)
{
	return !(u == v);
}