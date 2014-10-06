#ifndef POINTSET_H
#define POINTSET_H

#include "binaryserializable.h"
#include "point.h"
#include <vector>

class PointSet : public std::vector<Point>, public BinarySerializable
{
public:
    PointSet() {}

    explicit PointSet(size_type n, const Point &val = Point())
        : std::vector<Point>(n, val)
    {}

    template <class InputIterator>
    PointSet(InputIterator first, InputIterator last)
        : std::vector<Point>(first, last)
    {}

    PointSet(const std::vector<Point> &other)
        : std::vector<Point>(other)
    {}

    void addPoint(Point p) { push_back(p); }
    void removeLastPoint() { pop_back(); }

    virtual BinarySerializable* clone() const { return new PointSet(*this); }

    virtual int  binaryMarker() const;
    virtual int  requiredBufferSize() const;
    virtual void toBinaryBuffer(char *buffer, int offset, int buf_size) const;
    virtual void fromBinaryBuffer(const char *buffer, int offset, int buf_size);
};



#endif // POINTSET_H
