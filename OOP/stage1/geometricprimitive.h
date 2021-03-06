#ifndef ABSTRACTGEOMETRICFIGURE_H
#define ABSTRACTGEOMETRICFIGURE_H

#include "binaryserializable.h"
#include "painter.h"
#include "point.h"
#include "color.h"
#include <iostream>

class GeometricPrimitive : public BinarySerializable
{
public:
    virtual void  draw(Painter *painter) const = 0;
    virtual void  moveTo(Point where) = 0;
    virtual void  moveRelative(int dx, int dy) = 0;
    virtual void  rotate(double angle, Point rotation_center) = 0;
    void  rotate(double angle) { rotate(angle, massCenter()); }
    virtual Point massCenter() const = 0;

    virtual void printInfo(std::ostream &out) = 0;

    Color borderColor() const { return border_color_; }
    Color innerColor()  const { return inner_color_;  }
    void setBorderColor(Color border_color) { border_color_ = border_color; }
    void setInnerColor(Color inner_color)   { inner_color_ = inner_color;   }

protected:
    Color border_color_;
    Color inner_color_;
};

#endif // ABSTRACTGEOMETRICFIGURE_H
