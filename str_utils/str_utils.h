#ifndef _STR_UTILS_H
#define _STR_UTILS_H
/*********************************************************************
  providing some utils for string
 *********************************************************************/
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstring>
#include <climits>

std::vector<std::string> split(const std::string& str, const std::string& splitor = " ");
template<typename T>
std::vector<T> split(const std::string& str, const std::string& splitor = " ") {
  auto strvec = split(str, splitor);
  std::vector<T> result;
  result.reserve(strvec.size());
  T tmp;

  for (auto str : strvec) {
    std::istringstream is(str);
    is >> tmp;
    result.push_back(tmp);
  }

  return result;
}

template <typename T>
std::string join(const std::vector<T>& vecs, const std::string& splitor = " ", int istart = 0, int iend = -1) {
  std::ostringstream os;
  unsigned size = vecs.size();
  istart = (int(istart + (std::abs(istart) / size + 1) * size)) % size;
  iend = (int(iend + (std::abs(iend) / size + 1) * size)) % size;

  if (istart > iend) return "";

  for (unsigned i = istart; i < iend; i++) os << vecs[i] << splitor;
  os << vecs[iend];

  return os.str();
}

#endif // for #ifndef _STR_UTILS_H
