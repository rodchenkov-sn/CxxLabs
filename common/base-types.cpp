#include "base-types.hpp"
#include <cmath>

bool rodchenkov::isIntersected(const rectangle_t& lhs, const rectangle_t& rhs)
{
  return (fabs(lhs.pos.y - rhs.pos.y) < ((lhs.height + rhs.height) / 2) &&
      fabs(lhs.pos.x - rhs.pos.x) < ((lhs.width + rhs.width) / 2));
}
