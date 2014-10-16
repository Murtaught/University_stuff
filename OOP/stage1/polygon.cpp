#include "polygon.h"

#include "bytearray.h"

#define _USE_MATH_DEFINES
#include <cmath>

void Polygon::draw(Painter *painter) const
{
    painter->drawConvexPolygon(*this);
}

void Polygon::moveTo(Point where)
{
    if ( !points_.empty() )
    {
        int dx = where.x() - points_[0].x();
        int dy = where.y() - points_[0].y();

        moveRelative(dx, dy);
    }
}

void Polygon::moveRelative(int dx, int dy)
{
    for (std::vector<Point>::size_type i = 0; i < points_.size(); ++i)
        points_[i].moveRelative(dx, dy);
}

void Polygon::rotate(double angle, Point center)
{
    for (std::vector<Point>::iterator p = points_.begin(); p != points_.end(); ++p)
    {
        double diff_x    = p->x() - center.x();
        double diff_y    = p->y() - center.y();
        double length    = std::sqrt(diff_x * diff_x + diff_y * diff_y);
        double cur_angle = std::atan2(diff_y, diff_x) * (180.0 / M_PI);

        cur_angle += angle;
        cur_angle *= (M_PI / 180.0);

        double new_x = center.x() + length * std::cos(cur_angle);
        double new_y = center.y() + length * std::sin(cur_angle);

        p->moveTo(int(new_x), int(new_y));
    }
}

Point Polygon::massCenter() const
{
    int mc_x = 0, mc_y = 0;

    for (std::vector<Point>::size_type i = 0; i < points_.size(); ++i)
    {
        mc_x += points_[i].x();
        mc_y += points_[i].y();
    }

    mc_x /= points_.size();
    mc_y /= points_.size();

    return Point(mc_x, mc_y);
}

void Polygon::printInfo(std::ostream &out)
{
    out << "Polygon {";
    for (std::vector<Point>::size_type i = 0; i < points_.size(); ++i)
        out << " " << points_[i];
    out << " }";
}

int Polygon::binaryMarker() const
{
    // "Poly"
    return ('P') | ('o' << 8) | ('l' << 16) | ('y' << 24);
}

ByteArray::SizeType Polygon::requiredBufferSize() const
{
    return sizeof(binaryMarker()) + sizeof(border_color_) +
           sizeof(inner_color_) + ByteArray::requiredByteSize(points_);
}

void Polygon::toByteArray(ByteArray &byte_array) const
{
    byte_array.append(binaryMarker());
    byte_array.append(border_color_);
    byte_array.append(inner_color_);
    byte_array.append(points_);
}

void Polygon::fromByteArray(ByteArrayReader &bar)
{
    if (bar.bytesLeft() < sizeof( binaryMarker() ))
    {
        throw "Binary data is corrupted!";
    }

    int scanned_marker;
    bar >> scanned_marker;

    if (scanned_marker != binaryMarker())
    {
        throw "Given binary does not contain a Polygon!";
    }

    bar >> border_color_ >> inner_color_ >> points_;
}
