#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

class DataStruct
{
public:

  DataStruct() = default;
  DataStruct(int, int, std::string);

  bool operator < (const DataStruct& rhs) const;
  friend std::ostream& operator << (std::ostream& stream, const DataStruct& ds);
  friend std::istream& operator >> (std::istream& stream,DataStruct& ds);
  
  static int MIN_KEY;
  static int MAX_KEY;
  static std::string DELIM;

private:

  int         key_1_;
  int         key_2_;
  std::string str_;
};

#endif // DATA_STRUCT_HPP
