#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color
{
public:
    Color()
        : r_(0), g_(0), b_(0), a_(255)
    {}

    Color(int r, int g, int b, int a = 255)
        : r_(r), g_(g), b_(b), a_(a)
    {}

    Color(const Color &other)
    {
        reset(other.r(), other.g(), other.b(), other.a());
    }

    Color& operator=(const Color &other)
    {
        reset(other.r(), other.g(), other.b(), other.a());
        return *this;
    }

    int r() const { return r_; }
    int g() const { return g_; }
    int b() const { return b_; }
    int a() const { return a_; }

    void setR(int r) { r_ = r; }
    void setG(int g) { g_ = g; }
    void setB(int b) { b_ = b; }
    void setA(int a) { a_ = a; }

    void reset(int r, int g, int b, int a = 255)
    {
        setR(r); setG(g); setB(b); setA(a);
    }

private:
    int r_, g_, b_, a_;
};

std::istream& operator>>(std::istream &in, Color &color);
std::ostream& operator<<(std::ostream &out, const Color &color);

#endif // COLOR_H
