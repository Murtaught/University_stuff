#include "polygon.h"

void Polygon::draw(PainterAdapter */*painter*/)
{

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
    for (PointSet::size_type i = 0; i < points_.size(); ++i)
        points_[i].moveRelative(dx, dy);
}

void Polygon::rotate(int /*angle*/, Point /*rotation_center*/)
{

}

void Polygon::printInfo(std::ostream &out)
{
    out << "Polygon {";
    for (PointSet::size_type i = 0; i < points_.size(); ++i)
        out << " " << points_[i];
    out << " }";
}

int Polygon::binaryMarker() const
{
    // "Poly"
    return ('P') | ('o' << 8) | ('l' << 16) | ('y' << 24);
}

int Polygon::requiredBufferSize() const
{
    // first 4 bytes is always 'Poly' (binary marker)
    return 4 + points_.requiredBufferSize();
}

void Polygon::toBinaryBuffer(char *buffer, int offset, int buf_size) const
{
    if ((buf_size - offset) < requiredBufferSize())
    {
        throw "Given buffer is too small!";
    }

    int *header_address = (int*) (buffer + offset);
    header_address[0] = binaryMarker();

    points_.toBinaryBuffer(buffer, offset + 4, buf_size);
}

void Polygon::fromBinaryBuffer(const char *buffer, int offset, int buf_size)
{
    if ((buf_size - offset) < 8)
    {
        throw "Binary data is corrupted!";
    }

    int *header_address = (int*) (buffer + offset);
    if (header_address[0] != binaryMarker())
    {
        throw "Given binary does not contain a Polygon!";
    }

    points_.fromBinaryBuffer(buffer, offset + 4, buf_size);
}
