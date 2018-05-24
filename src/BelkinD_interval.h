#pragma once
#include <algorithm>

namespace BelkinD {

class Interval
{
public:
    Interval(                                     ) : m_left(0.                   ), m_right(0.                   ) { }
    Interval(const double left, const double right) : m_left(std::min(left, right)), m_right(std::max(left, right)) { }

    double Left () const { return m_left;  }
    double Right() const { return m_right; }

    void SetLeft (const double left ) { m_left  = left;  }
    void SetRight(const double right) { m_right = right; }

    void Sort()
    {
        if (m_left > m_right) std::swap(m_left, m_right);
    }

    bool intersectsInterval(Interval & interval);

private:
    double m_left;
    double m_right;
};

}
