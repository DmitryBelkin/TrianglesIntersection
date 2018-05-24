#pragma once
#include <cassert>

namespace BelkinD {

enum class Coordinate
{
    X,
    Y,
    Z,
};

class Vector
{
public:
    Vector( ) : m_x1(0.), m_y1(0.), m_z1(0.), m_x0(0.), m_y0(0.), m_z0(0.) { }
    Vector(const double x1, const double y1, const double z1) : m_x1(x1), m_y1(y1), m_z1(z1), m_x0(0.), m_y0(0.), m_z0(0.) { }
    Vector(const double x1, const double y1, const double z1,
           const double x0, const double y0, const double z0)
    : m_x1(x1), m_y1(y1), m_z1(z1),
      m_x0(x0), m_y0(y0), m_z0(z0) { }

    double operator * (Vector v)
    {
        const auto v1 = v.getVectorCoordinates();
        const auto v2 = this->getVectorCoordinates();
        return v2.x1() * v1.x1() + v2.x1() * v1.y1() + v2.x1() * v1.z1();
    }

    void operator () (Vector & v1, Vector & v2)
    {
        const auto v1Coord = v1.getVectorCoordinates();
        const auto v2Coord = v2.getVectorCoordinates();
        m_x1 = v1Coord.y1() * v2Coord.z1() - v1Coord.z1() * v2Coord.y1();
        m_y1 = v1Coord.z1() * v2Coord.x1() - v1Coord.x1() * v2Coord.z1();
        m_z1 = v1Coord.x1() * v2Coord.y1() - v1Coord.y1() * v2Coord.x1();
        m_x0 = 0; m_y0 = 0; m_z0 = 0;
    }

    friend Vector operator - (Vector & v1, Vector & v2)
    {
        const auto v1Coord = v1.getVectorCoordinates();
        const auto v2Coord = v2.getVectorCoordinates();
        return Vector(v1Coord.x1() - v2Coord.x1(), v1Coord.y1() - v2Coord.y1(), v1Coord.z1() - v2Coord.z1());
    }
    
    double x1() const { return m_x1; }
    double y1() const { return m_y1; }
    double z1() const { return m_z1; }

    double x0() const { return m_x0; }
    double y0() const { return m_y0; }
    double z0() const { return m_z0; }

    Vector getVectorCoordinates() const
    {
        return Vector(m_x1 - m_x0, m_y1 - m_y0, m_z1 - m_z0);
    }

    double getCoordinate(Coordinate coordinate) const
    {
        const auto v = getVectorCoordinates();
        return v.getEndCoordinate(coordinate);
    }

    double getEndCoordinate(Coordinate coordinate) const
    {
        if (coordinate == Coordinate::X) return x1();
        if (coordinate == Coordinate::Y) return y1();
        if (coordinate == Coordinate::Z) return z1();
        assert(!"Invalid ccordinate");
        return 0;
    }

    double getBeginCoordinate(Coordinate coordinate) const
    {
        if (coordinate == Coordinate::X) return x0();
        if (coordinate == Coordinate::Y) return y0();
        if (coordinate == Coordinate::Z) return z0();
        assert(!"Invalid ccordinate");
        return 0;
    }

    void setX1(const double x1) { m_x1 = x1; }
    void setY1(const double y1) { m_y1 = y1; }
    void setZ1(const double z1) { m_z1 = z1; }

    void setX0(const double x0) { m_x0 = x0; }
    void setY0(const double y0) { m_y0 = y0; }
    void setZ0(const double z0) { m_z0 = z0; }

public:
    double m_x1;
    double m_y1;
    double m_z1;

    double m_x0;
    double m_y0;
    double m_z0;
};

}
