#include "phoneBook.hpp"

PhoneBook::PageIterator PhoneBook::begin()
{
  return pages_.begin();
}

PhoneBook::ConstPageIterator PhoneBook::cbegin() const noexcept
{
  return pages_.cbegin();
}

PhoneBook::PageIterator PhoneBook::end()
{
  return pages_.end();
}

PhoneBook::ConstPageIterator PhoneBook::cend() const noexcept
{
  return pages_.cend();
}

bool PhoneBook::empty() const noexcept
{
  return pages_.empty();
}

size_t PhoneBook::size() const noexcept
{
  return pages_.size();
}

void PhoneBook::insertAfter(PageIterator pageIter, const std::string& name, const std::string& phone)
{
  if (pageIter != pages_.end()) {
    ++pageIter;
  }
  if (pageIter == pages_.end()) {
    pages_.push_back({ name, phone });
  } else {
    pages_.insert(pageIter, { name, phone });
  }
}

void PhoneBook::insertBefore(PageIterator pageIter, const std::string& name, const std::string& phone)
{
  pages_.insert(pageIter, { name, phone });
}

void PhoneBook::append(const std::string& name, const std::string& phone)
{
  pages_.push_back({ name, phone });
}

void PhoneBook::remove(PageIterator pageIter)
{
  pages_.erase(pageIter);
}
