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
        return Vector(p1.X() - p2.X(), p1.Y() - p2.Y(), p1.Z() - p2.Z());
    }

    double X() const { return X1(); }
    double Y() const { return Y1(); }
    double Z() const { return Z1(); }

    void SetX(const double x) { SetX1(x); }
    void SetY(const double y) { SetY1(y); }
    void SetZ(const double z) { SetZ1(z); }

    double GetCoordinate(Coordinate coordinate) const
    {
        return GetEndCoordinate(coordinate);
    }
};

}
