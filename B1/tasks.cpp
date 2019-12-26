#include "tasks.hpp"

#include <iterator>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <forward_list>
#include <memory>

#include "sorting.hpp"
#include "accessStrategy.hpp"

void task1(const std::string& ordering)
{
  std::function<bool(const int&, const int&)> comparator;
  if (ordering == "ascending") {
    comparator = std::less<>{};
  }
  else if (ordering == "descending") {
    comparator = std::greater<>{};
  }
  else {
    throw std::invalid_argument{ "usage: > lab1 1 (ascending|descending)" };
  }
  std::vector<int> seq{};
  int curr;
  while (std::cin >> curr, !std::cin.eof()) {
    if (!std::cin.eof() && std::cin.fail()) {
      throw std::runtime_error{ "In task #1 Integer sequence required." };
    }
    seq.push_back(curr);
  }
  if (seq.empty()) {
    return;
  }
  std::vector<int> idCollection{ seq.begin(), seq.end() };
  std::vector<int> atCollection{ seq.begin(), seq.end() };
  std::forward_list<int> itCollection{ seq.begin(), seq.end() };

  sort<IndexAccess>(idCollection, comparator);
  sort<AtAccess>(atCollection, comparator);
  sort<IteratorAccess>(itCollection, comparator);

  std::move(idCollection.begin(), idCollection.end(), std::ostream_iterator<int>{ std::cout, " " }); std::cout << "\n";
  std::move(atCollection.begin(), atCollection.end(), std::ostream_iterator<int>{ std::cout, " " }); std::cout << "\n";
  std::move(itCollection.begin(), itCollection.end(), std::ostream_iterator<int>{ std::cout, " " });
}

void task2(const std::string& filePath)
{
  std::ifstream fin{ filePath };
  if (!fin.is_open()) {
    throw std::runtime_error{ "could not open \"" + filePath + "\"" };
  }

  size_t contentSize = 0, contentCapacity = 16;
  std::unique_ptr<char[], decltype(&free)> fileContent{ static_cast<char*>(malloc(contentCapacity)), free };

  while (fin) {
    fin.read(&fileContent[contentSize], contentCapacity - contentSize);
    contentSize += fin.gcount();
    if (contentSize == contentCapacity) {
      contentCapacity *= 2;
      auto old = fileContent.release();
      fileContent.reset(static_cast<char*>(std::realloc(old, contentCapacity)));
      if (!fileContent) {
        throw std::runtime_error{ "could not allocate memory for file content" };
      }
    }
  }

  fin.close();
  if (fin.is_open()) {
    throw std::runtime_error{ "could not close \"" + filePath + "\"" };
  }
  std::vector<char> content{ &fileContent[0], &fileContent[contentSize] };
  std::copy(content.begin(), content.end(), std::ostream_iterator<char>{ std::cout });
}

void task3()
{
  std::vector<int> seq{};
  int curr = 0;
  while (std::cin >> curr, !std::cin.eof()) {
    if (std::cin.fail()) {
      throw std::runtime_error{ "In task #3 Integer sequence required." };
    }
    if (curr == 0) {
      break;
    }
    seq.push_back(curr);
  }
  if (curr != 0) {
    throw std::runtime_error{ "In task #3 terminating '0' expected." };
  }
  if (seq.empty()) {
    return;
  }
  if (seq.back() == 1) {
    auto iter = seq.begin();
    while (iter != seq.end()) {
      if (*iter % 2 == 0) {
        iter = seq.erase(iter);
      }
      else {
        ++iter;
      }
    }
  }
  else if (seq.back() == 2) {
    auto iter = seq.begin();
    while (iter != seq.end()) {
      if (*iter % 3 == 0) {
        iter = seq.insert(iter + 1, 3, 1) + 3;
      }
      else {
        ++iter;
      }
    }
  }
  std::copy(seq.begin(), seq.end(), std::ostream_iterator<int>{ std::cout, " " });
}

void fillRandom(double* arr, size_t size)
{
  std::uniform_real_distribution<double> distr{ -1, 1 };
  std::default_random_engine engine{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
  for (size_t i = 0; i < size; i++) {
    arr[i] = distr(engine);
  }
}

void task4(const std::string& ordering, const std::string& sizeStr)
{
  int size = std::stoi(sizeStr);
  if (size <= 0) {
    throw std::invalid_argument{ "vector size must be positive" };
  }
  std::vector<double> randSeq(size);
  fillRandom(randSeq.data(), size);
  std::function<bool(const double&, const double&)> comparator;
  if (ordering == "ascending") {
    comparator = std::less<>{};
  }
  else if (ordering == "descending") {
    comparator = std::greater<>{};
  }
  else {
    throw std::invalid_argument{ "usage: > lab1 4 (ascending|descending) vector_size" };
  }
  std::copy(randSeq.begin(), randSeq.end(), std::ostream_iterator<double>{ std::cout, " " }); std::cout << "\n";
  sort<IteratorAccess>(randSeq, comparator);
  std::move(randSeq.begin(), randSeq.end(), std::ostream_iterator<double>{ std::cout, " " }); std::cout << "\n";
}
