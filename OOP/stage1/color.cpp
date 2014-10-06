#include "color.h"

namespace
{
    int readOctet(std::istream &in)
    {
        static const char digits[] = "0123456789ABCDEF";

        char c; in >> c;
        if ('a' <= c && c <= 'z') c -= 'a' - 'A';

        for (int i = 0; i < 16; ++i)
            if (c == digits[i])
                return i;

        return -1;
    }

    int readByteInHex(std::istream &in)
    {
        int a = readOctet(in);
        int b = readOctet(in);

        std::cout << "read octets: " << (a) << " " << (b) << std::endl;

        return (a << 4) + b;
    }

    void writeByteInHex(std::ostream &out, int byte)
    {
        static const char digits[] = "0123456789ABCDEF";

        out << digits[byte >> 4] << digits[byte & 0x0F];
    }
}

std::istream &operator>>(std::istream &in, Color &color)
{
    char c = ' ';
    while (c != '#')
        in >> c;

    color.setR( readByteInHex(in) );
    color.setG( readByteInHex(in) );
    color.setB( readByteInHex(in) );
    color.setA( readByteInHex(in) );

    return in;
}


std::ostream &operator<<(std::ostream &out, const Color &color)
{
    out << '#';
    writeByteInHex(out, color.r());
    writeByteInHex(out, color.g());
    writeByteInHex(out, color.b());
    writeByteInHex(out, color.a());

    return out;
}
