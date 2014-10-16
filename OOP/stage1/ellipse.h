#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "geometricprimitive.h"
#include "painter.h"
#include "point.h"
#include "color.h"

class Ellipse : public GeometricPrimitive
{
public:
    Ellipse();
    Ellipse(const Point &center, int rx, int ry);
    Ellipse(const Ellipse &other);

    Point  center() const { return center_; }
    double angle() const  { return angle_;  }
    int rx() const { return rx_; }
    int ry() const { return ry_; }

    void setCenter(const Point &center) { center_ = center; }
    void setAngle(double angle)         { angle_ = angle;   }
    void setRx(int rx) { rx_ = rx; }
    void setRy(int ry) { ry_ = ry; }

    virtual void  draw(Painter *painter) const;
    virtual void  moveTo(Point where);
    virtual void  moveRelative(int dx, int dy);
    virtual void  rotate(double angle, Point rotation_center);
    virtual Point massCenter() const;

    virtual void printInfo(std::ostream &out);

    virtual BinarySerializable* clone() const { return new Ellipse(*this); }

    virtual int  binaryMarker() const;
    virtual ByteArray::SizeType requiredBufferSize() const;
    virtual void toByteArray(ByteArray &byte_array) const;
    virtual void fromByteArray(ByteArrayReader &bar);

protected:
    Point center_;
    double angle_;
    int rx_;
    int ry_;
};

#endif // ELLIPSE_H
