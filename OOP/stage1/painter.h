#ifndef PAINTERADAPTER_H
#define PAINTERADAPTER_H

class Point;
class Color;
class Polygon;
class Ellipse;

// Это интерфейс
class Painter
{
public:
    virtual ~Painter() {}

    // Пермеместить центр системы координат в точку where относительно текущего центра
    virtual void translate(const Point& where) = 0;

    // Повернуть СК на angle градусов против часовой стрелки
    virtual void rotate(double angle) = 0;

    // Сохранить / текущую СК (действует как стек)
    virtual void save()    = 0; // push
    virtual void restore() = 0; // pop

    // Устаовить цвет линий и цвет заливки
    virtual void setBorderLineColor(const Color &color) = 0;
    virtual void setInnerFillColor(const Color &color) = 0;

    // Нарисовать примитив
    virtual void drawLine(const Point &p1, const Point& p2) = 0;
    virtual void drawConvexPolygon(const Polygon &poly) = 0;
    virtual void drawEllipse(const Ellipse &ellipse) = 0;
};

#endif // PAINTERADAPTER_H
