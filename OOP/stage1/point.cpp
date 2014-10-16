#include "point.h"

std::istream& operator>>(std::istream &in, Point &p)
{
    int x, y;
    in >> x >> y;
    p.moveTo(x, y);
    return in;
}

std::ostream& operator<<(std::ostream &out, const Point &p)
{
    out << "(" << p.x() << ", " << p.y() << ")";
    return out;
}

bool leftAndBelow(const Point &pa, const Point &pb)
{
    if (pa.x() == pb.x())
        return pa.y() < pb.y();

    return pa.x() < pb.x();
}

bool rightAndUp(const Point &pa, const Point &pb)
{
    if (pa.x() == pb.x())
        return pa.y() > pb.y();

    return pa.x() > pb.x();
}

Point &Point::operator+=(const Point &other)
{
    x_ += other.x_;
    y_ += other.y_;
    return *this;
}

Point &Point::operator-=(const Point &other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
}

Point operator+(Point a, const Point &b)
{
    a += b;
    return a;
}

Point operator-(Point a, const Point &b)
{
    a -= b;
    return a;
}

bool operator==(const Point &a, const Point &b)
{
    return (a.x() == b.x()) && (a.y() == b.y());
}

bool operator!=(const Point &a, const Point &b)
{
    return !(a == b);
}
