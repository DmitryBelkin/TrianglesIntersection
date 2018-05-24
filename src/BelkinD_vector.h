#pragma once

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
    Vector(double x1, double y1, double z1) : m_x1(x1), m_y1(y1), m_z1(z1), m_x0(0.), m_y0(0.), m_z0(0.) { }
    Vector(double x1, double y1, double z1,
           double x0, double y0, double z0)
    : m_x1(x1), m_y1(y1), m_z1(z1),
      m_x0(x0), m_y0(y0), m_z0(z0) { }

    double operator * (Vector v)
    {
        const auto v1 = v.GetVectorCoordinates();
        const auto v2 = this->GetVectorCoordinates();
        return v2.X1() * v1.X1() + v2.Y1() * v1.Y1() + v2.Z1() * v1.Z1();
    }

    friend Vector operator - (Vector & v1, Vector & v2)
    {
        const auto v1Coord = v1.GetVectorCoordinates();
        const auto v2Coord = v2.GetVectorCoordinates();
        return Vector(v1Coord.X1() - v2Coord.X1(), v1Coord.Y1() - v2Coord.Y1(), v1Coord.Z1() - v2Coord.Z1());
    }

    void operator () (Vector & v1, Vector & v2);
    
    double X1() const { return m_x1; }
    double Y1() const { return m_y1; }
    double Z1() const { return m_z1; }

    double X0() const { return m_x0; }
    double Y0() const { return m_y0; }
    double Z0() const { return m_z0; }

    Vector GetVectorCoordinates() const
    {
        return Vector(m_x1 - m_x0, m_y1 - m_y0, m_z1 - m_z0);
    }

    double GetCoordinate(Coordinate coordinate) const
    {
        const auto v = GetVectorCoordinates();
        return v.GetEndCoordinate(coordinate);
    }

    double GetEndCoordinate(Coordinate coordinate) const;
    double GetBeginCoordinate(Coordinate coordinate) const;

    void SetX1(const double x1) { m_x1 = x1; }
    void SetY1(const double y1) { m_y1 = y1; }
    void SetZ1(const double z1) { m_z1 = z1; }

    void SetX0(const double x0) { m_x0 = x0; }
    void SetY0(const double y0) { m_y0 = y0; }
    void SetZ0(const double z0) { m_z0 = z0; }

private:
    double m_x1;
    double m_y1;
    double m_z1;

    double m_x0;
    double m_y0;
    double m_z0;
};

}
