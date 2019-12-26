#include "phoneBookInterface.hpp"
#include <algorithm>

const std::string PhoneBookInterface::invalidBM = "<INVALID BOOKMARK>\n";
const std::string PhoneBookInterface::currentBM = "current";

PhoneBookInterface::PhoneBookInterface()
{
  book_marks_.insert({ currentBM, phone_book_.begin() });
}

void PhoneBookInterface::add(const std::string& phone, const std::string& name)
{
  phone_book_.append(name, phone);
  revalidate_();
}

std::string PhoneBookInterface::storeBm(const std::string& currBM, const std::string& newBM)
{
  if (book_marks_.find(currBM) == book_marks_.end() || book_marks_.find(newBM) != book_marks_.end()) {
    return invalidBM;
  }
  book_marks_.insert({ newBM, book_marks_.at(currBM) });
  return "";
}

std::string PhoneBookInterface::insertBefore(const std::string& bookMark, const std::string& phone, const std::string& name)
{
  if (book_marks_.find(bookMark) == book_marks_.end()) {
    return invalidBM;
  }
  phone_book_.insertBefore(book_marks_.at(bookMark), name, phone);
  revalidate_();
  return "";
}

std::string PhoneBookInterface::insertAfter(const std::string& bookMark, const std::string& phone, const std::string& name)
{
  if (book_marks_.find(bookMark) == book_marks_.end()) {
    return invalidBM;
  }
  phone_book_.insertAfter(book_marks_.at(bookMark), name, phone);
  revalidate_();
  return "";
}

std::string PhoneBookInterface::remove(const std::string& bookMark)
{
  if (book_marks_.find(bookMark) == book_marks_.end()) {
    return invalidBM;
  }
  const auto oldBM = book_marks_.at(bookMark);
  std::for_each(book_marks_.begin(), book_marks_.end(), [&](auto& p) { if (p.second == oldBM) {
      ++p.second;
    }
  });
  phone_book_.remove(oldBM);
  revalidate_();
  return "";
}

std::string PhoneBookInterface::show(const std::string& bookMark)
{
  if (book_marks_.find(bookMark) == book_marks_.end()) {
    return invalidBM;
  }
  if (phone_book_.empty()) {
    return "<EMPTY>\n";
  }
  return book_marks_.at(bookMark)->phone + " " + book_marks_.at(bookMark)->name + "\n";
}

std::string PhoneBookInterface::advance(const std::string& bookMark, long long steps)
{
  if (book_marks_.find(bookMark) == book_marks_.end()) {
    return invalidBM;
  }
  auto it = book_marks_.at(bookMark);
  while (steps > 0 && it != phone_book_.end()) {
    ++it;
    --steps;
  }
  while (steps < 0 && it != phone_book_.begin()) {
    --it;
    ++steps;
  }
  if (it == phone_book_.end()) {
    --it;
  }
  book_marks_.at(bookMark) = it;
  return "";
}

std::string PhoneBookInterface::moveToFirst(const std::string& bookMark)
{
  if (book_marks_.find(bookMark) == book_marks_.end()) {
    return invalidBM;
  }
  book_marks_.at(bookMark) = phone_book_.begin();
  return "";
}

std::string PhoneBookInterface::moveToLast(const std::string& bookMark)
{
  if (book_marks_.find(bookMark) == book_marks_.end()) {
    return invalidBM;
  }
  if (!phone_book_.empty()) {
    book_marks_.at(bookMark) = --phone_book_.end();
  }
  return "";
}

void PhoneBookInterface::revalidate_()
{
  if (!phone_book_.empty()) {
    std::for_each(book_marks_.begin(), book_marks_.end(), [&](auto& p) {
      if (p.second == phone_book_.end()) p.second = --p.second;
      });
  }
}
