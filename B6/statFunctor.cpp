#include "statFunctor.hpp"

#include <algorithm>

StatFunctor::StatFunctor():
  min_(std::numeric_limits<int>::max()),
  max_(std::numeric_limits<int>::min()),
  avg_(0),
  count_(0),
  pos_count_(0),
  neg_count_(0),
  even_sum_(0),
  odd_sum_(0),
  first_(0),
  fst_eq_lst_(false)
{
}

void StatFunctor::operator()(int x)
{
  if (count_ == 0) {
    first_ = x;
  }
  max_ = std::max(x, max_);
  min_ = std::min(x, min_);
  avg_ = (avg_ * count_ + x) / (count_ + 1);
  if (x > 0) {
    ++pos_count_;
  } else if (x < 0) {
    ++neg_count_;
  }
  if (x % 2 == 0) {
    even_sum_ += x;
  } else {
    odd_sum_ += x;
  }
  fst_eq_lst_ = first_ == x;
  ++count_;
}


std::ostream& operator<<(std::ostream& stream, const StatFunctor& sf)
{
  std::ostream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  if (sf.count_ == 0) {
    stream << "No Data";
    return stream;
  }
  stream <<   "Max: "              << sf.max_
         << "\nMin: "              << sf.min_
         << "\nMean: "             << std::fixed << sf.avg_
         << "\nPositive: "         << sf.pos_count_
         << "\nNegative: "         << sf.neg_count_
         << "\nOdd Sum: "          << sf.odd_sum_
         << "\nEven Sum: "         << sf.even_sum_
         << "\nFirst/Last Equal: " << (sf.fst_eq_lst_ ? "yes" : "no");
  return stream;
}
