#include "BelkinD_vector.h"

#include <cassert>

namespace BelkinD {

void Vector::operator () (Vector & v1, Vector & v2)
{
    const auto v1Coord = v1.GetVectorCoordinates();
    const auto v2Coord = v2.GetVectorCoordinates();
    m_x1 = v1Coord.Y1() * v2Coord.Z1() - v1Coord.Z1() * v2Coord.Y1();
    m_y1 = v1Coord.Z1() * v2Coord.X1() - v1Coord.X1() * v2Coord.Z1();
    m_z1 = v1Coord.X1() * v2Coord.Y1() - v1Coord.Y1() * v2Coord.X1();
    m_x0 = 0; m_y0 = 0; m_z0 = 0;
}

double Vector::GetEndCoordinate(Coordinate coordinate) const
{
    if (coordinate == Coordinate::X) return X1();
    if (coordinate == Coordinate::Y) return Y1();
    if (coordinate == Coordinate::Z) return Z1();
    assert(!"Invalid ccordinate");
    return 0;
}

double Vector::GetBeginCoordinate(Coordinate coordinate) const
{
    if (coordinate == Coordinate::X) return X0();
    if (coordinate == Coordinate::Y) return Y0();
    if (coordinate == Coordinate::Z) return Z0();
    assert(!"Invalid ccordinate");
    return 0;
}

}
