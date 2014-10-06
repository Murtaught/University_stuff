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
