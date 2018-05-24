#pragma once
#include <algorithm>

namespace BelkinD {

class Interval
{
public:
    Interval(                                     ) : m_left(0.                   ), m_right(0.                   ) { }
    Interval(const double left, const double right) : m_left(std::min(left, right)), m_right(std::max(left, right)) { }

    double left () const { return m_left;  }
    double right() const { return m_right; }

    void setLeft (const double left ) { m_left  = left;  }
    void setRight(const double right) { m_right = right; }

    void sort()
    {
        if (m_left > m_right) std::swap(m_left, m_right);
    }

    bool intersectsInterval(Interval & interval)
    {
        sort(); // @todo SRP
        interval.sort(); // @todo SRP
        if (m_right < interval.left() || interval.right() < m_left) return false;
        return true;
    }

private:
    double m_left;
    double m_right;
};

}
