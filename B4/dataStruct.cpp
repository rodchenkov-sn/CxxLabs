#include "dataStruct.hpp"

#include <utility>

#include "ioUtils.hpp"

int DataStruct::MIN_KEY = -5;
int DataStruct::MAX_KEY = 5;
std::string DataStruct::DELIM = ", ";

DataStruct::DataStruct(int k1, int k2, std::string s):
  key_1_(k1),
  key_2_(k2),
  str_(std::move(s))
{
  if (k1 < MIN_KEY || k1 > MAX_KEY) {
    throw std::invalid_argument{ "unexpected key1 value" };
  }
  if (k2 < MIN_KEY || k2 > MAX_KEY) {
    throw std::invalid_argument{ "unexpected key2 value" };
  }
}

bool DataStruct::operator<(const DataStruct& rhs) const
{
  if (key_1_ != rhs.key_1_) {
    return key_1_ < rhs.key_1_;
  }
  if (key_2_ != rhs.key_2_) {
    return key_2_ < rhs.key_2_;
  }
  return str_.length() < rhs.str_.length();

}

std::ostream& operator<<(std::ostream& stream, const DataStruct& ds)
{
  std::ostream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  stream << ds.key_1_ << DataStruct::DELIM << ds.key_2_ << DataStruct::DELIM << ds.str_;
  return stream;
}

std::istream& operator>>(std::istream& stream, DataStruct& ds)
{
  int k1 = 0, k2 = 0;
  std::string s{};

  std::istream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }

  FlagGuard guard{ stream };

  stream >> std::noskipws
         >> ws >> k1 >> ws >> readDelim<char>(',')
         >> ws >> k2 >> ws >> readDelim<char>(',') >> ws;
  std::getline(stream, s);
  if (!stream.fail()) {
    ds = { k1, k2, s };
  }
  return stream;
}
