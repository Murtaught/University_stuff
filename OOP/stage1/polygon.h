#ifndef POLYGON_H
#define POLYGON_H

#include "geometricprimitive.h"
#include "painter.h"
#include "point.h"
#include "pointset.h"
#include "color.h"

class Polygon : public GeometricPrimitive
{
public:
    Polygon()
    {}

    explicit Polygon(const PointSet &points)
        : points_(points)
    {}

    Polygon(const Polygon &other)
        : points_(other.points_)
    {}

    const PointSet& points() const { return points_; }

    virtual void draw(Painter *painter);
    virtual void moveTo(Point where);
    virtual void moveRelative(int dx, int dy);
    virtual void rotate(int angle, Point rotation_center);

    virtual void printInfo(std::ostream &out);

    virtual BinarySerializable* clone() const
    {
        return new Polygon(*this);
    }

    virtual int  binaryMarker() const;
    virtual int  requiredBufferSize() const;
    virtual void toBinaryBuffer(char *buffer, int offset, int buf_size) const;
    virtual void fromBinaryBuffer(const char *buffer, int offset, int buf_size);

protected:
    PointSet points_;
};

#endif // POLYGON_H
