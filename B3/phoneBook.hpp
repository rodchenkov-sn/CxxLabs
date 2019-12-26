#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP
#include <string>
#include <list>

class PhoneBook
{

  struct page_t
  {
    std::string name;
    std::string phone;
  };

public:

  using PageIterator = std::list<page_t>::iterator;
  using ConstPageIterator = std::list<page_t>::const_iterator;

  PageIterator begin();
  ConstPageIterator cbegin() const noexcept;
  PageIterator end();
  ConstPageIterator cend() const noexcept;
  bool empty() const noexcept;
  size_t size() const noexcept;
  void insertAfter(PageIterator, const std::string&, const std::string&);
  void insertBefore(PageIterator, const std::string&, const std::string&);
  void append(const std::string&, const std::string&);
  void remove(PageIterator);

private:

  std::list<page_t> pages_;
};

#endif // PHONE_BOOK_HPP
