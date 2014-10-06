#include "pointset.h"

int PointSet::binaryMarker() const
{
    // "PSet"
    return ('P') | ('s' << 8) | ('e' << 16) | ('t' << 24);
}

int PointSet::requiredBufferSize() const
{
    // Marker, size (4 bytes each) and 8 bytes for evey point
    return sizeof(int) * (2 + this->size() * 2);
}

void PointSet::toBinaryBuffer(char *buffer, int offset, int buf_size) const
{
    int *convenient_buf = (int*) (buffer + offset);

    if ((buf_size - offset) < requiredBufferSize())
    {
        throw "Given buffer is too small!";
    }

    convenient_buf[0] = binaryMarker();
    convenient_buf[1] = size();

    int cur_offset = 1;
    for (size_type i = 0; i < size(); ++i)
    {
        convenient_buf[++cur_offset] = (*this)[i].x();
        convenient_buf[++cur_offset] = (*this)[i].y();
    }
}

void PointSet::fromBinaryBuffer(const char *buffer, int offset, int buf_size)
{
    const int *convenient_buf = (const int*) (buffer + offset);
    buf_size -= offset;

    if (convenient_buf[0] != binaryMarker())
    {
        throw "Given binary does not contain a Point Set!";
    }

    int size = convenient_buf[1];
    resize(size);

    if (buf_size < requiredBufferSize())
    {
        throw "Binary data is corrupted!";
    }

    for (int i = 0; i < size; ++i)
        (*this)[i].moveTo(convenient_buf[2 + i * 2], convenient_buf[3 + i * 2]);
}
