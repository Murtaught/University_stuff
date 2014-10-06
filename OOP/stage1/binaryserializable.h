#ifndef BINARYSERIALIZABLE_H
#define BINARYSERIALIZABLE_H

class BinarySerializable
{
public:
    virtual BinarySerializable* clone() const = 0;
    virtual ~BinarySerializable() {}

    virtual int  binaryMarker() const = 0;
    virtual int  requiredBufferSize() const = 0;
    virtual void toBinaryBuffer(char *buffer, int offset, int buf_size) const = 0;
    virtual void fromBinaryBuffer(const char *buffer, int offset, int buf_size) = 0;
};

#endif // BINARYSERIALIZABLE_H
