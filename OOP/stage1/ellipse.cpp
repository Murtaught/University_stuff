#include "ellipse.h"
#include "bytearray.h"

Ellipse::Ellipse()
    : center_(0, 0),
      angle_(0),
      rx_(0),
      ry_(0)
{}

Ellipse::Ellipse(const Point &center, int rx, int ry)
    : center_(center),
      angle_(0),
      rx_(rx),
      ry_(ry)
{}

Ellipse::Ellipse(const Ellipse &other)
    : center_(other.center_),
      angle_(other.angle_),
      rx_(other.rx_),
      ry_(other.ry_)
{}

void Ellipse::moveTo(Point where)
{
    center_ = where;
}

void Ellipse::moveRelative(int dx, int dy)
{
    center_.moveRelative(dx, dy);
}

void Ellipse::rotate(double angle, Point rotation_center)
{
    if (rotation_center == center_)
    {
        angle_ += angle;
        while (angle_ > 360.0)
            angle_ -= 360.0;
    }
    else
    {
        // TODO
    }
}

Point Ellipse::massCenter() const
{
    return center_;
}

void Ellipse::printInfo(std::ostream &out)
{
    out << "Ellipse { center: " << center() << ", "
           "angle: " << angle() << ", "
           "width/height: " << rx_ << " / " << ry_ << ", "
           "colors (border/inner): " << border_color_ << " / " << inner_color_ << " }";
}

int Ellipse::binaryMarker() const
{
    // "Elps"
    return ('E') | ('l' << 8) | ('p' << 16) | ('s' << 24);
}

ByteArray::SizeType Ellipse::requiredBufferSize() const
{
    return sizeof(center_) + sizeof(angle_) +
           sizeof(rx_) + sizeof(ry_) +
           sizeof(border_color_) + sizeof(inner_color_);
}

void Ellipse::toByteArray(ByteArray &byte_array) const
{
    byte_array << binaryMarker()
               << center_
               << angle_
               << rx_
               << ry_
               << border_color_
               << inner_color_;
}

void Ellipse::fromByteArray(ByteArrayReader &bar)
{
    if (bar.bytesLeft() < requiredBufferSize())
    {
        throw "Binary data is corrupted!";
    }

    int scanned_marker;
    bar.scanNext(scanned_marker);

    if (scanned_marker != binaryMarker())
    {
        throw "Given binary does not contain an Ellipse!";
    }

    bar >> center_
        >> angle_
        >> rx_
        >> ry_
        >> border_color_
        >> inner_color_;
}

void Ellipse::draw(Painter* painter) const
{
    painter->save();
        painter->translate(center_);
        painter->rotate(angle_);
        painter->setBorderLineColor(border_color_);
        painter->setInnerFillColor(inner_color_);
        painter->drawEllipse(*this);
    painter->restore();
}



