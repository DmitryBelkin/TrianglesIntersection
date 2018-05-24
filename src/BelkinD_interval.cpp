#include "BelkinD_interval.h"

namespace BelkinD {

bool Interval::intersectsInterval(Interval & interval)
{
    Sort(); // @todo SRP
    interval.Sort(); // @todo SRP
    if (m_right < interval.Left() || interval.Right() < m_left) return false;
    return true;
}

}
