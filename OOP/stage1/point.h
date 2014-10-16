#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
    Point() : x_(0), y_(0) {}
    Point(int x, int y) : x_(x), y_(y) {}
    Point(const Point &other) : x_(other.x()), y_(other.y()) {}

    Point& operator=(const Point &other)
    {
        moveTo(other.x(), other.y());
        return *this;
    }

    int x() const { return x_; } // implicitly inline
    int y() const { return y_; }
    void setX(int value) { x_ = value; }
    void setY(int value) { y_ = value; }

    Point& operator+=(const Point &other);
    Point& operator-=(const Point &other);

    void moveTo(int x, int y) { setX(x); setY(y); }
    void moveRelative(int dx, int dy) { x_ += dx; y_ += dy; }

private:
    int x_, y_;
};

bool operator==(const Point &a, const Point &b);
bool operator!=(const Point &a, const Point &b);

Point operator+(Point a, const Point &b);
Point operator-(Point a, const Point &b);

// some comparators
bool leftAndBelow(const Point &pa, const Point &pb);
bool rightAndUp(const Point &pa, const Point &pb);

// for text streams (not binary!)
std::istream& operator>>(std::istream &in, Point &p);
std::ostream& operator<<(std::ostream &out, const Point &p);

#endif // POINT_H
