#ifndef VECTORPICTURE_H
#define VECTORPICTURE_H

#include "binaryserializable.h"
#include "geometricprimitive.h"
#include <vector>

class VectorPicture : public std::vector<GeometricPrimitive*>, public BinarySerializable
{
public:
    VectorPicture() {}

    explicit VectorPicture(size_type n) : std::vector<GeometricPrimitive*>(n) {}

    template <class InputIterator>
    VectorPicture(InputIterator first, InputIterator last)
        : std::vector<GeometricPrimitive*>(first, last)
    {}

    VectorPicture(const std::vector<GeometricPrimitive*> &other)
        : std::vector<GeometricPrimitive*>(other)
    {}

    virtual BinarySerializable* clone() const
    {
        return new VectorPicture(*this);
    }

    virtual int  binaryMarker() const;
    virtual ByteArray::SizeType requiredBufferSize() const;
    virtual void toByteArray(ByteArray &byte_array) const;
    virtual void fromByteArray(ByteArrayReader &bar);
};

#endif // VECTORPICTURE_H
