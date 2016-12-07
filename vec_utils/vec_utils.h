#ifndef _VEC_UTILS_H
#define _VEC_UTILS_H
/*********************************************************************
  providing some utils for vector
 *********************************************************************/
#include<vector>
#include<iostream>
#include<cstring>
#include<climits>

int get_index(const std::vector <double> &vec, double x);
int get_index(const double *arr, unsigned dim, double x);

#define VECTOR_UTILS_OSTREAM(types)\
  std::ostream& operator<< (std::ostream& out, const std::vector <types> &vec);\
  std::ostream& operator<< (std::ostream& out, const std::vector <std::vector <types> > &vec);

VECTOR_UTILS_OSTREAM(int)
VECTOR_UTILS_OSTREAM(double)
VECTOR_UTILS_OSTREAM(std::string)

#define VECTOR_UTILS_OPERATOR(opers)\
  std::vector <double> operator opers (const std::vector <double> &lhs,const std::vector <double> &rhs);\
  std::vector <double> operator opers (const double &lhs,const std::vector <double> &rhs);\
  std::vector <double> operator opers (const std::vector <double> &lhs,const double &rhs);

VECTOR_UTILS_OPERATOR(+)
VECTOR_UTILS_OPERATOR(-)
VECTOR_UTILS_OPERATOR(*)
VECTOR_UTILS_OPERATOR( /)

namespace vec_utils {
  template<typename TI, typename TO> void map(const std::vector<TI>& input, std::vector<TO>& output, TO (*function)(const TI&)) {
    output.clear();
    output.reserve(input.size());
    for (auto iter = input.begin(); iter != input.end(); iter++)
      output.push_back(function(*iter));
  }

  template<typename TI, typename TO> void pair_map(const std::vector<TI>& input, std::vector<TO>& output, TO (*function)(const TI&, const TI&)) {
    output.clear();
    if (input.size() <= 1) return;

    output.reserve(input.size() - 1);
    auto iter = input.begin(),
         seciter = iter;
    seciter++;
    for (; seciter != input.end();) {
      output.push_back(function(*iter, *seciter));
      iter++;
      seciter++;
    }
  }

  template<typename T> int index(const std::vector<T>& array, const T& term) {
    for(int i = 0; i < array.size(); i++)
      if (array[i] == term) return i;
    return -1;
  }
}
#endif // for #ifndef _VEC_UTILS_H
