/*********************************************************************/ 
// use this class to deal Physical array ,with name and util
/*********************************************************************/ 
#ifndef _PARRAY_H
#define _PARRAY_H
#include <iostream>
#include <string>

class pArray 
{
public:
  double * a;

  pArray();
  pArray(int _Length,
         std::string _Name,
         std::string _Unit = "not set",
         std::string _Comments = "no comments");
  pArray(const pArray &);
  ~pArray();

  std::string GetName() const;
  std::string GetUnit() const;
  std::string GetComments() const;
  int GetLength() const;

  void SetUtil(std::string);
  void SetComments(std::string);

  pArray & operator=(const pArray &);
  pArray & operator=(const double *);
  pArray & operator=(const float *);
#define PARRAY_OPERATOR(oper, opers)\
  pArray & operator opers(const double &);\
  pArray & operator opers(const pArray &);\
  pArray operator oper(const double &) const;\
  pArray operator oper(const pArray &) const;\
  friend pArray operator oper(const double &lhs, const pArray &rhs);

  PARRAY_OPERATOR(+, +=)
  PARRAY_OPERATOR(-, -=)
  PARRAY_OPERATOR(*, *=)
  PARRAY_OPERATOR(/, /=)
  PARRAY_OPERATOR(^, ^=)
#undef PARRAY_OPERATOR

  friend std::ostream & operator<<(std::ostream & out,const pArray & ref);

private:
  std::string Name;
  std::string Unit;
  std::string Comments;
  int Length;
};

pArray operator +(const double &lhs, const pArray &rhs);
pArray operator -(const double &lhs, const pArray &rhs);
pArray operator *(const double &lhs, const pArray &rhs);
pArray operator /(const double &lhs, const pArray &rhs);
pArray operator ^(const double &lhs, const pArray &rhs);
std::ostream & operator<<(std::ostream & out, const pArray & ref);
#endif
