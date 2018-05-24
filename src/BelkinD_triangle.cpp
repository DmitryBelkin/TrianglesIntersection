#include "BelkinD_triangle.h"
#include "BelkinD_point.h"
#include "BelkinD_interval.h"

#include <cmath>

namespace BelkinD {

inline bool Check2Edges(const Point & v0,
                        const Point & u0, const Point & u1,
                        const Coordinate abscissa, const Coordinate ordinate,
                        const double Ax, const double Ay)
{
    const auto B = u0 - u1;
    const auto C = v0 - u0;

    const auto Bx = B.GetCoordinate(abscissa);
    const auto By = B.GetCoordinate(ordinate);
    const auto Cx = C.GetCoordinate(abscissa);
    const auto Cy = C.GetCoordinate(ordinate);

    const auto f = Ay * Bx - Ax * By;
    const auto d = By * Cx - Bx * Cy;

    double e;
    if((f > 0 && d >= 0 && d <= f) || (f < 0 && d <= 0 && d >= f))
    {
        e = Ax * Cy - Ay * Cx;
        if (f > 0)
        {
            if (e >= 0 && e <= f)
                return true;
        }
        else
        {
            if(e <= 0 && e >= f)
                return true;
        }
    }

    return false;
}

inline bool CheckEdgeAgainst3Edges(const Point & v0, const Point & v1,
                                   const Point & u0, const Point & u1, const Point & u2,
                                   const Coordinate abscissa, const Coordinate ordinate)
{
    const auto A  = v1 - v0;
    const auto Ax = A.GetCoordinate(abscissa);
    const auto Ay = A.GetCoordinate(ordinate);

    if (Check2Edges(v0, u0, u1, abscissa, ordinate, Ax, Ay)) return true;
    if (Check2Edges(v0, u1, u2, abscissa, ordinate, Ax, Ay)) return true;
    if (Check2Edges(v0, u2, u0, abscissa, ordinate, Ax, Ay)) return true;

    return false;
}

inline bool IsPointInTriangle(const Point & v0,
                              const Point & u0, const Point & u1, const Point & u2,
                              const Coordinate abscissa, const Coordinate ordinate)
{
    double a, b, c;
    // @todo make function for plane
    a         =       u1.GetCoordinate(ordinate) -     u0.GetCoordinate(ordinate);
    b         = -    (u1.GetCoordinate(abscissa) -     u0.GetCoordinate(abscissa));
    c         = - a * u0.GetCoordinate(abscissa) - b * u0.GetCoordinate(ordinate);
    double d0 =   a * v0.GetCoordinate(abscissa) + b * v0.GetCoordinate(ordinate) + c;

    a         =       u2.GetCoordinate(ordinate) -     u1.GetCoordinate(ordinate);
    b         = -    (u2.GetCoordinate(abscissa) -     u1.GetCoordinate(abscissa));
    c         = - a * u1.GetCoordinate(abscissa) - b * u1.GetCoordinate(ordinate);
    double d1 =   a * v0.GetCoordinate(abscissa) + b * v0.GetCoordinate(ordinate) + c;

    a         =       u0.GetCoordinate(ordinate) -     u2.GetCoordinate(ordinate);
    b         = -    (u0.GetCoordinate(abscissa) -     u2.GetCoordinate(abscissa));
    c         = - a * u2.GetCoordinate(abscissa) - b * u2.GetCoordinate(ordinate);
    double d2 =   a * v0.GetCoordinate(abscissa) + b * v0.GetCoordinate(ordinate) + c;

    if (d0 * d1 > 0.0)
    {
        if(d0 * d2 > 0.0)
            return true;
    }

    return false;
}

inline bool CalculateIntervalForCoplanarTriangles(const Vector & n,
                      const Point & v0, const Point & v1, const Point & v2,
                      const Point & u0, const Point & u1, const Point & u2)
{
    double nFabs[3];
    nFabs[0] = fabs(n.X1());
    nFabs[1] = fabs(n.Y1());
    nFabs[2] = fabs(n.Z1());
    Coordinate abscissa = Coordinate::X;
    Coordinate ordinate = Coordinate::Y;
    if (nFabs[0] > nFabs[1])
    {
        if (nFabs[0] > nFabs[2]) { abscissa = Coordinate::Y; ordinate = Coordinate::Z; }
        else                     { abscissa = Coordinate::X; ordinate = Coordinate::Y; }
    }
    else
    {
        if (nFabs[2] > nFabs[1]) { abscissa = Coordinate::X; ordinate = Coordinate::Y; }
        else                     { abscissa = Coordinate::X; ordinate = Coordinate::Z; }
    }

    if (CheckEdgeAgainst3Edges(v0, v1, u0, u1, u2, abscissa, ordinate)) return true;
    if (CheckEdgeAgainst3Edges(v1, v2, u0, u1, u2, abscissa, ordinate)) return true;
    if (CheckEdgeAgainst3Edges(v2, v0, u0, u1, u2, abscissa, ordinate)) return true;

    if (IsPointInTriangle(v0, u0, u1, u2, abscissa, ordinate)) return true;
    if (IsPointInTriangle(u0, v0, v1, v2, abscissa, ordinate)) return true;

    return false;
}

inline void CalcInterval(const double p0, const double p1, const double p2, const double d0, const double d1, const double d2, Interval & interval)
{
    interval.SetLeft (p0 + (p1 - p0) * d0 / (d0 - d1));
    interval.SetRight(p0 + (p2 - p0) * d0 / (d0 - d2));
}

bool CalculateIntersectionIntervals(const double p0, const double p1, const double p2,
                                    const double d0, const double d1, const double d2,
                                    const double d0d1, const double d0d2,
                                    Interval & interval)
{
    if      (d0d1 > 0.0)                 { CalcInterval(p2, p0, p1, d2, d0, d1, interval); return true; }
    else if (d0d2 > 0.0)                 { CalcInterval(p1, p0, p2, d1, d0, d2, interval); return true; }
    else if (d1 * d2 > 0.0 || d0 != 0.0) { CalcInterval(p0, p1, p2, d0, d1, d2, interval); return true; }
    else if (d1 != 0.0)                  { CalcInterval(p1, p0, p2, d1, d0, d2, interval); return true; }
    else if (d2 != 0.0)                  { CalcInterval(p2, p0, p1, d2, d0, d1, interval); return true; }

    return false;
}

bool AreTrianglesIntersect(double t1[9], double t2[9])
{
    Point v0(t1[0], t1[1], t1[2]);
    Point v1(t1[3], t1[4], t1[5]);
    Point v2(t1[6], t1[7], t1[8]);

    Point u0(t2[0], t2[1], t2[2]);
    Point u1(t2[3], t2[4], t2[5]);
    Point u2(t2[6], t2[7], t2[8]);

    Vector e1 = v1 - v0;
    Vector e2 = v2 - v0;
    Vector n1;
    n1(e1, e2);
    auto d1 = - (n1 * v0);

    auto du0 = n1 * u0 + d1;
    auto du1 = n1 * u1 + d1;
    auto du2 = n1 * u2 + d1;

    if (fabs(du0) < std::numeric_limits<double>::epsilon()) du0 = 0.0;
    if (fabs(du1) < std::numeric_limits<double>::epsilon()) du1 = 0.0;
    if (fabs(du2) < std::numeric_limits<double>::epsilon()) du2 = 0.0;

    const auto du0du1 = du0 * du1;
    const auto du0du2 = du0 * du2;

    if(du0du1 > 0.0f && du0du2 > 0.0f)
        return false;

    e1 = u1 - v0;
    e2 = u2 - v0;
    Vector n2;
    n2(e1, e2);
    auto d2 = - (n2 * u0);

    auto dv0 = n2 * v0 + d2;
    auto dv1 = n2 * v1 + d2;
    auto dv2 = n2 * v2 + d2;

    if (fabs(dv0) < std::numeric_limits<double>::epsilon()) dv0 = 0.0;
    if (fabs(dv1) < std::numeric_limits<double>::epsilon()) dv1 = 0.0;
    if (fabs(dv2) < std::numeric_limits<double>::epsilon()) dv2 = 0.0;

    const auto dv0dv1 = dv0 * dv1;
    const auto dv0dv2 = dv0 * dv2;

    if(dv0dv1 > 0.0 && dv0dv2 > 0.0)
        return false;

    Vector D;
    D(n1, n2);

    auto max = fabs(D.X1());
    Coordinate coord = Coordinate::X;
    const auto b = fabs(D.Y1());
    const auto c = fabs(D.Z1());

    if (b > max) { max = b; coord = Coordinate::Y; }
    if (c > max) { max = c; coord = Coordinate::Z; }

    const auto vp0 = v0.GetCoordinate(coord);
    const auto vp1 = v1.GetCoordinate(coord);
    const auto vp2 = v2.GetCoordinate(coord);

    const auto up0 = u0.GetCoordinate(coord);
    const auto up1 = u1.GetCoordinate(coord);
    const auto up2 = u2.GetCoordinate(coord);

    Interval intervalForTriangle1;
    if (!CalculateIntersectionIntervals(vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, intervalForTriangle1))
        return CalculateIntervalForCoplanarTriangles(n1, v0, v1, v2, u0, u1, u2);

    Interval intervalForTriangle2;
    CalculateIntersectionIntervals(up0, up1, up2, du0, du1, du2, du0du1, du0du2, intervalForTriangle2);

    if (!intervalForTriangle1.intersectsInterval(intervalForTriangle2))
        return false;

    return true;
}

}
