#include "vectorpicture.h"
#include "binarymarkerdispatcher.h"

int VectorPicture::binaryMarker() const
{
    // "VPic"
    return ('V') | ('P' << 8) | ('i' << 16) | ('c' << 24);
}

int VectorPicture::requiredBufferSize() const
{
    // Our 4-byte marker, then 4-byte size and every primitive
    int sum = 8;
    for (size_type i = 0; i < size(); ++i)
        sum += (*this)[i]->requiredBufferSize();

    return sum;
}

void VectorPicture::toBinaryBuffer(char *buffer, int offset, int buf_size) const
{
    if ((buf_size - offset) < requiredBufferSize())
    {
        throw "Given buffer is too small!";
    }

    int *header_address = (int*) (buffer + offset);
    header_address[0] = binaryMarker();
    header_address[1] = (int) size();

    int offset_acc = 0;
    for (size_type i = 0; i < size(); ++i)
    {
        GeometricPrimitive *primitive = (*this)[i];

        primitive->toBinaryBuffer(buffer, offset + 8 + offset_acc, buf_size);
        offset_acc += primitive->requiredBufferSize();
    }
}

void VectorPicture::fromBinaryBuffer(const char *buffer, int offset, int buf_size)
{
    if ((buf_size - offset) < 8)
    {
        throw "Binary data is corrupted!";
    }

    int *header_address = (int*) (buffer + offset);
    if (header_address[0] != binaryMarker())
    {
        throw "Given binary buffer does not contain a Vector Picture!";
    }

    // extract size from header
    resize(header_address[1]);

    const BinaryMarkerDispatcher &dispatcher = *BinaryMarkerDispatcher::instance();

    int offset_acc = 0;
    for (size_type i = 0; i < size(); ++i)
    {
        int primitive_marker = *((const int*) (buffer + offset + 8 + offset_acc));
        GeometricPrimitive *primitive = (GeometricPrimitive*) (dispatcher.dispatchMarker(primitive_marker));

        primitive->fromBinaryBuffer(buffer, offset + 8 + offset_acc, buf_size);
        (*this)[i] = primitive;

        offset_acc += primitive->requiredBufferSize();
    }
}
