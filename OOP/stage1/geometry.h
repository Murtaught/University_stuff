#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>

template <typename T>
class Point
{
public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}

    T getX() const { return x; }
    T getY() const { return y; }
    void setX(const T &value) { x = value; }
    void setY(const T &value) { y = value; }

    void reset(T x, T y) { setX(x); setY(y); }

private:
    T x, y;
};

template <typename T>
std::istream& operator>>(std::istream &in, Point<T> &p)
{
    T x, y;
    in >> x >> y;
    p.reset(x, y);
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream &out, const Point<T> &p)
{
    out << "(" << p.getX() << ", " << p.getY() << ")";
    return out;
}

#endif // GEOMETRY_H
