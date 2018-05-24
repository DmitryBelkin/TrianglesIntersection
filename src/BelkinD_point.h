#pragma once
#include "BelkinD_vector.h"

namespace BelkinD {

class Point : public Vector
{
public:
    Point( ) : Vector() { }
    Point(const double x, const double y, const double z) : Vector(x, y, z) { }

    friend Vector operator - (const Point & p1, const Point & p2)
    {
        return Vector(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
    }

    double x() const { return x1(); }
    double y() const { return y1(); }
    double z() const { return z1(); }

    void setX(const double x) { setX1(x); }
    void setY(const double y) { setY1(y); }
    void setZ(const double z) { setZ1(z); }

    double getCoordinate(Coordinate coordinate) const
    {
        return getEndCoordinate(coordinate);
    }
};

}
