#include "Point.hh"

#include <cmath>

using namespace std;

// *****************************************************************************

Point::Point(double x, double y) : x(x), y(y) {}

Point::~Point() {}

double Point::get_X() const {
    return x;
}

double Point::get_Y() const {
    return y;
}

double Point::distance(const Point &p) const {
    double dx = get_X() - p.get_X();
    double dy = get_Y() - p.get_Y();
    return sqrt(dx*dx + dy*dy);
}

double Point::radius() const {
    return sqrt(get_X()*get_X() + get_Y()*get_Y());
}

double Point::angle() const {
    if (isEqual(get_X(), 0) and isEqual(get_Y(), 0)) return 0;
    return atan(get_Y() / get_X());
}

double Point::slope(const Point &p) const {
    if (isEqual(p.get_X(), get_X())) return INF;
	return (p.get_Y() - get_Y()) / (p.get_X() - get_X());
}

bool Point::operator == (const Point &p) const {
    return isEqual(get_X(), p.get_X()) and isEqual(get_Y(), p.get_Y());
}

bool Point::operator != (const Point &p) const {
    return not(*this == p);
}

bool Point::operator < (const Point& p) const {
    if (isEqual(get_X(), p.get_X())) {
        return (get_Y() < p.get_Y()) and not isEqual(get_Y(), p.get_Y());
    } else {
        return get_X() < p.get_X() and not isEqual(get_X(), p.get_X());
    }
}

bool Point::operator > (const Point& p) const {
    if (isEqual(get_X(), p.get_X())) {
        return (get_Y() > p.get_Y()) and not isEqual(get_Y(), p.get_Y());
    } else {
        return get_X() > p.get_X() and not isEqual(get_X(), p.get_X());
    }
}

Point Point::operator + (const Point &p) const {
    return Point(get_X() + p.get_X(), get_Y() + p.get_Y());
}

Point Point::operator += (const Point &p) {
    x += p.get_X();
    y += p.get_Y();
    return *this;
}

Point Point::operator * (const double &d) const {
    return Point(d*get_X(), d*get_Y());
}

Point Point::operator *= (const double &d) {
    x *= d;
    y *= d;
    return *this;
}





