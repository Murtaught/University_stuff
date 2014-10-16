#ifndef POLYGON_H
#define POLYGON_H

#include "geometricprimitive.h"
#include "painter.h"
#include "point.h"
#include "color.h"
#include <vector>

class Polygon : public GeometricPrimitive
{
public:
    Polygon()
    {}

    explicit Polygon(const std::vector<Point> &points)
        : points_(points)
    {}

    Polygon(const Polygon &other)
        : points_(other.points_)
    {}

    const std::vector<Point>& points() const { return points_; }
    void setPoints(const std::vector<Point> &points) { points_ = points; }

    virtual void  draw(Painter *painter) const;
    virtual void  moveTo(Point where);
    virtual void  moveRelative(int dx, int dy);
    virtual void  rotate(double angle, Point rotation_center);
    virtual Point massCenter() const;

    virtual void printInfo(std::ostream &out);

    virtual BinarySerializable* clone() const { return new Polygon(*this); }

    virtual int  binaryMarker() const;
    virtual ByteArray::SizeType requiredBufferSize() const;
    virtual void toByteArray(ByteArray &byte_array) const;
    virtual void fromByteArray(ByteArrayReader &bar);

protected:
     std::vector<Point> points_;
};

#endif // POLYGON_H
