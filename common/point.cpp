#include "point.hpp"

#include <iterator>
#include <boost/format.hpp>

#include "ioUtils.hpp"

const std::string point_t::PRINT_FMT = "(%1%;%2%)";

std::ostream& operator<<(std::ostream& stream, const point_t& point)
{
  std::ostream::sentry sentry{ stream };
  if (sentry) {
    stream << boost::format(point_t::PRINT_FMT) % point.x % point.y;
  }
  return stream;
}

std::istream& operator>>(std::istream& stream, point_t& point)
{
  int x, y;
  std::istream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  FlagGuard flagGuard{ stream };
  stream >> std::noskipws
         >> ws >> readDelim<char>('(') >> ws >> x
         >> ws >> readDelim<char>(';') >> ws >> y
         >> ws >> readDelim<char>(')');
  if (!stream.fail()) {
    point = { x, y };
  }
  return stream;
}
