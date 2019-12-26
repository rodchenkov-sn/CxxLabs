#ifndef COMMON_IO_UTILS_HPP
#define COMMON_IO_UTILS_HPP

#include <istream>
#include <functional>

std::istream& ws(std::istream&);

std::string readUntil(std::istream&, const std::function<bool(char)>&);

template <typename T>
class readDelim
{
public:
  explicit readDelim(T delimiter):
    delimiter_(delimiter)
  {
  }

  friend std::istream& operator >>(std::istream& stream, const readDelim& d)
  {
    std::istream::sentry sentry{ stream };
    if (!sentry) {
      return stream;
    }
    T delim;
    stream >> delim;
    if (stream.fail() || delim != d.delimiter_) {
      stream.setstate(std::ios_base::failbit);
      return stream;
    }
    return stream;
  }

private:
  T delimiter_;
};

class FlagGuard
{
public:
  explicit FlagGuard(std::ios_base&);

  FlagGuard(const FlagGuard&) = delete;
  FlagGuard(FlagGuard&&) = delete;
  FlagGuard& operator = (const FlagGuard&) = delete;
  FlagGuard& operator = (FlagGuard&&) = delete;


  ~FlagGuard();
private:
  std::ios_base& stream_;
  std::ios_base::fmtflags flags_;
};

#endif // COMMON_IO_UTILS_HPP
