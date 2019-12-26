#ifndef STAT_FUNCTOR_HPP
#define STAT_FUNCTOR_HPP

#include <ostream>

class StatFunctor
{
public:
  StatFunctor();
  void operator() (int x);
  friend std::ostream& operator << (std::ostream&, const StatFunctor&);
private:
  int     min_;
  int     max_;
  double  avg_;
  size_t  count_;
  size_t  pos_count_;
  size_t  neg_count_;
  int64_t even_sum_;
  int64_t odd_sum_;
  int     first_;
  bool    fst_eq_lst_;
};

#endif // STAT_FUNCTOR_HPP
