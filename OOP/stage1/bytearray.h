#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <vector>

class ByteArray
{
public:
    typedef std::vector<char> ContainerType;
    typedef ContainerType::size_type SizeType;

    ByteArray() {}

    ByteArray(const char *data, SizeType size)
        : array_(data, data + size)
    {}

    ByteArray(const ByteArray &other)
        : array_(other.array_)
    {}

    SizeType size() const { return array_.size(); }

    template <typename T>
    void append(const T &t)
    {
        array_.resize(size() + sizeof(T));

        char *byte_ptr = &array_[size() - sizeof(T)];
        T *T_ptr = reinterpret_cast<T*>(byte_ptr);
        (*T_ptr) = t;
    }

    template <typename T>
    void append(const std::vector<T> &vt)
    {
        append(vt.size());
        for (typename std::vector<T>::const_iterator it = vt.begin(); it != vt.end(); ++it)
            append(*it);
    }

    template <typename T>
    static SizeType requiredByteSize(const T &t)
    {
        return sizeof(T);
    }

    template <typename T>
    static SizeType requiredByteSize(const std::vector<T> &vt)
    {
        return sizeof(vt.size()) + vt.size() * sizeof(T);
    }

    void chop(SizeType bytes_amount) { array_ .resize(size() - bytes_amount); }
    void clear() { array_.clear(); }

    const char* data() const { return array_.data(); }
    std::vector<char> copy() const { return array_; }

    void copyContentsTo(char *buffer, int size) const
    {
        for (int i = 0; i < size; ++i)
            buffer[i] = array_[i];
    }

    template <typename T>
    SizeType scan(SizeType offset, T &t) const
    {
        if ((size() - offset) < sizeof(T))
            throw "This buffer is too small to contain an item of such type!";

        const T *T_ptr = reinterpret_cast<const T*>(data() + offset);
        t = *T_ptr;

        return offset + sizeof(T);
    }

    template <typename T>
    SizeType scan(SizeType offset, std::vector<T> &vt) const
    {
        SizeType vt_size;
        offset = scan(offset, vt_size);

        if ((size() - offset) < (vt_size * sizeof(T)))
            throw "This buffer is too small to contain a vector of such type!";

        vt.resize(vt_size);
        for (typename std::vector<T>::iterator it = vt.begin(); it != vt.end(); ++it)
            offset = scan(offset, *it);

        return offset;
    }

private:
    ContainerType array_;
};

class ByteArrayReader
{
public:
    ByteArrayReader(const ByteArray *byte_array)
        : byte_array_(byte_array),
          offset_(0)
    {}

    void setByteArray(const ByteArray *byte_array)
    {
        byte_array_ = byte_array;
        offset_ = 0;
    }

    void reset() { offset_ = 0; }
    void setOffset(ByteArray::SizeType offset) { offset_ = offset; }
    void skip(ByteArray::SizeType bytes_amount) { offset_ += bytes_amount; }
    void unread(ByteArray::SizeType bytes_amount) { offset_ -= bytes_amount; }

    template <typename T>
    void scanNext(T &t)
    {
        offset_ = byte_array_->scan(offset_, t);
    }

    ByteArray::SizeType bytesLeft() const { return byte_array_->size() - offset_; }

private:
    const ByteArray *byte_array_;
    ByteArray::SizeType offset_;
};

template <typename T>
ByteArrayReader& operator>>(ByteArrayReader &bar, T &t)
{
    bar.scanNext(t);
    return bar;
}

template <typename T>
ByteArray& operator<<(ByteArray &ba, const T &t)
{
    ba.append(t);
    return ba;
}

#endif // BYTEARRAY_H
