#include "ioUtils.hpp"

FlagGuard::FlagGuard(std::ios_base& stream):
  stream_(stream),
  flags_(stream.flags())
{
}

FlagGuard::~FlagGuard()
{
  stream_.flags(flags_);
}

std::istream& ws(std::istream& stream)
{
  std::istream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  while (isblank(stream.peek())) {
    stream.get();
  }
  return stream;
}

std::string readUntil(std::istream& stream, const std::function<bool(char)>& isDelim)
{
  std::istream::sentry sentry{ stream };
  if (!sentry) {
    return {};
  }
  std::string res;
  char c;
  while (!isDelim(stream.peek())) {
    stream.get(c);
    res += c;
  }
  return res;
}
