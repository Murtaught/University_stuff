#include "vectorpicture.h"
#include "binarymarkerdispatcher.h"
#include "bytearray.h"

int VectorPicture::binaryMarker() const
{
    // "VPic"
    return ('V') | ('P' << 8) | ('i' << 16) | ('c' << 24);
}

ByteArray::SizeType VectorPicture::requiredBufferSize() const
{
    ByteArray::SizeType sum = sizeof(binaryMarker()) + sizeof(size_type);
    for (size_type i = 0; i < size(); ++i)
        sum += (*this)[i]->requiredBufferSize();

    return sum;
}

void VectorPicture::toByteArray(ByteArray &byte_array) const
{
    byte_array << binaryMarker() << size();

    for (size_type i = 0; i < size(); ++i)
        (*this)[i]->toByteArray(byte_array);
}

void VectorPicture::fromByteArray(ByteArrayReader &bar)
{
    if (bar.bytesLeft() < sizeof(binaryMarker()) + sizeof(size_type))
    {
        throw "Binary data is corrupted!";
    }

    int scanned_marker; bar >> scanned_marker;
    if (scanned_marker != binaryMarker())
    {
        throw "Given binary buffer does not contain a Vector Picture!";
    }

    int scanned_size; bar >> scanned_size;
    resize(scanned_size);

    const BinaryMarkerDispatcher &dispatcher = *BinaryMarkerDispatcher::instance();
    for (size_type i = 0; i < size(); ++i)
    {
        int primitive_marker;
        bar >> primitive_marker;
        bar.unread(sizeof(primitive_marker));

        // dispatcher выкинет исключение если такой маркер не зарегистрирован
        (*this)[i] = dynamic_cast<GeometricPrimitive*>(dispatcher.dispatchMarker(primitive_marker));
        (*this)[i]->fromByteArray(bar);
    }
}
