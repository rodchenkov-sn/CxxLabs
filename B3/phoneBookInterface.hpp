#ifndef PHONE_BOOK_INTERFACE_HPP
#define PHONE_BOOK_INTERFACE_HPP

#include <unordered_map>

#include "phoneBook.hpp"

class PhoneBookInterface
{
public:
  PhoneBookInterface();
  void add(const std::string& phone, const std::string&);
  std::string storeBm(const std::string&, const std::string&);
  std::string insertBefore(const std::string&, const std::string&, const std::string&);
  std::string insertAfter(const std::string&, const std::string&, const std::string&);
  std::string remove(const std::string&);
  std::string show(const std::string&);
  std::string advance(const std::string&, long long);
  std::string moveToFirst(const std::string&);
  std::string moveToLast(const std::string&);
private:

  void revalidate_();

  static const std::string invalidBM;
  static const std::string currentBM;

  PhoneBook phone_book_;
  std::unordered_map<std::string, PhoneBook::PageIterator> book_marks_;
};

#endif // PHONE_BOOK_INTERFACE_HPP
