#ifndef ACCESS_STRATEGY_HPP
#define ACCESS_STRATEGY_HPP

#include <stddef.h>

template <typename ContainerType>
class IndexAccess
{
public:
  using Container = ContainerType;
  using SizeType = size_t;
  using Element = typename Container::reference;

  static Element  get(Container&, SizeType);
  static SizeType begin(const Container&);
  static SizeType end(const Container&);
  static SizeType inc(SizeType);
};

template <typename Container>
typename IndexAccess<Container>::Element IndexAccess<Container>::get(Container& c, SizeType i)
{
  return c[i];
}

template <typename Container>
typename IndexAccess<Container>::SizeType IndexAccess<Container>::begin(const Container&)
{
  return 0;
}

template <typename Container>
typename IndexAccess<Container>::SizeType IndexAccess<Container>::end(const Container& c)
{
  return c.size();
}

template <typename Container>
typename IndexAccess<Container>::SizeType IndexAccess<Container>::inc(SizeType i)
{
  return ++i;
}

template <typename ContainerType>
class AtAccess
{
public:
  using Container = ContainerType;
  using SizeType  = size_t;
  using Element   = typename Container::reference;

  static Element  get(Container&, SizeType);
  static SizeType begin(const Container&);
  static SizeType end(const Container&);
  static SizeType inc(SizeType);
};

template <typename Container>
typename AtAccess<Container>::Element AtAccess<Container>::get(Container& c, SizeType i)
{
  return c.at(i);
}

template <typename Container>
typename AtAccess<Container>::SizeType AtAccess<Container>::begin(const Container&)
{
  return 0;
}

template <typename Container>
typename AtAccess<Container>::SizeType AtAccess<Container>::end(const Container& c)
{
  return c.size();
}

template <typename Container>
typename AtAccess<Container>::SizeType AtAccess<Container>::inc(SizeType i)
{
  return ++i;
}

template <typename ContainerType>
class IteratorAccess
{
public:
  using Container = ContainerType;
  using SizeType  = typename Container::iterator;
  using Element   = typename Container::reference;

  static Element  get(Container&, SizeType);
  static SizeType begin(Container&);
  static SizeType end(Container&);
  static SizeType inc(SizeType);
};

template <typename Container>
typename IteratorAccess<Container>::Element IteratorAccess<Container>::get(Container&, SizeType i)
{
  return *i;
}

template <typename Container>
typename IteratorAccess<Container>::SizeType IteratorAccess<Container>::begin(Container& c)
{
  return c.begin();
}

template <typename Container>
typename IteratorAccess<Container>::SizeType IteratorAccess<Container>::end(Container& c)
{
  return c.end();
}

template <typename Container>
typename IteratorAccess<Container>::SizeType IteratorAccess<Container>::inc(SizeType i)
{
  return ++i;
}

#endif // ACCESS_STRATEGY_HPP
