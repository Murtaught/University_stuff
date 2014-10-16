#ifndef BINARYSERIALIZABLE_H
#define BINARYSERIALIZABLE_H

#include "bytearray.h"

class BinarySerializable
{
public:
    virtual BinarySerializable* clone() const = 0;
    virtual ~BinarySerializable() {}

    virtual int  binaryMarker() const = 0;
    virtual ByteArray::SizeType requiredBufferSize() const = 0;
    virtual void toByteArray(ByteArray &byte_array) const = 0;
    virtual void fromByteArray(ByteArrayReader &bar) = 0;

    ByteArray toByteArray() const
    {
        ByteArray byte_array;
        toByteArray(byte_array);
        return byte_array;
    }
};

#endif // BINARYSERIALIZABLE_H
