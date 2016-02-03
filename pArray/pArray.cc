/*********************************************************************/ 
//Name: mdArray.cc
//Author: weicc
//Email: ccwei@itp.ac.cn
//Date: 01-02-2016
/*********************************************************************/ 
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "pArray.h"
using namespace std;

pArray::pArray():Name("not set"),
                 Unit("not set"),
                 Comments("no commemts"),
                 Length(1) {
  a = new double[Length];
  memset(a, 0, Length*sizeof(double));
}
pArray::pArray(int _Length,
               std::string _Name,
               std::string _Unit,
               std::string _Comments ):Name(_Name),
                                       Unit(_Unit),
                                       Comments(_Comments),
                                       Length(_Length) {
  a = new double[Length];
  memset(a, 0, Length*sizeof(double));
}
pArray::pArray(const pArray & ref) {
  Length = ref.GetLength();
  Name = ref.GetName();
  Unit = ref.GetUnit();
  Comments = ref.GetComments();

  a = new double[Length];
  copy(ref.a, ref.a + Length, a);
}
pArray::~pArray() {
  delete []a;
}
//**********************************************************************
std::string pArray::GetName() const {
  return Name;
}
std::string pArray::GetUnit() const {
  return Unit;
}
std::string pArray::GetComments() const {
  return Comments;
}
int pArray::GetLength() const {
  return Length;
}
void pArray::SetUtil(std::string _Unit) {
  Unit = _Unit;
}
void pArray::SetComments(std::string _Comments) {
  Comments = _Comments;
}
//**********************************************************************
pArray & pArray::operator=(const pArray & ref) {
  if(this != &ref) {
    Name = ref.GetName();
    Unit = ref.GetUnit();
    Comments = ref.GetComments();
    Length = ref.GetLength();

    delete []a;
    a = new double[Length];
    copy(ref.a, ref.a + Length, a);
  }
  return *this;
}
pArray & pArray::operator=(const double * ref) {
  copy(ref, ref + Length, a);
  return *this;
}
pArray & pArray::operator=(const float * ref) {
  copy(ref, ref + Length, a);
  return *this;
}
//**********************************************************************
#define NOT_DIVIDE(lhs, ope, rhs, res) res = lhs ope rhs
#define DIVIDE(lhs, ope, rhs, res)\
  if(rhs == 0) res=0;\
  else res = lhs ope rhs

#define NOT_POW(div_or_not, lhs, ope, rhs, res)\
  div_or_not(lhs, ope, rhs, res)
#define POW(div_or_not, lhs, ope, rhs, res)\
  res = pow(lhs, rhs)

#define OPERFUNC(oper, opers, div_or_not, pow_or_not)\
  pArray operator oper(const double &lhs, const pArray &rhs) {\
    pArray result(rhs);\
    for(int i=0; i<result.GetLength(); i++) {\
      pow_or_not(div_or_not, lhs, oper, rhs.a[i], result.a[i]);\
    }\
    return result;\
  }\
  pArray & pArray::operator opers(const pArray &rhs) {\
    if(Unit != rhs.GetUnit() || Length != rhs.GetLength()) {\
      cout<<"ERROR: operate with differnt form of pArray"<<endl;\
      cout<<"       pArray1: "<<Name<<"\t"<<Unit<<"\t"<<Length<<endl;\
      cout<<"       pArray2: "<<rhs.GetName()<<"\t"<<rhs.GetUnit()<<"\t"<<rhs.GetLength()<<endl;\
      exit(1);\
    }\
    for(int i=0; i<Length; i++) {\
      pow_or_not(div_or_not, a[i], opers, rhs.a[i], a[i]);\
    }\
    return *this;\
  }\
  pArray & pArray::operator opers(const double &rhs) {\
    for(int i=0; i<Length; i++) {\
      pow_or_not(div_or_not, a[i], opers, rhs, a[i]);\
    }\
    return *this;\
  }\
  pArray pArray::operator oper(const pArray &rhs) const {\
    pArray result(*this);\
    result opers rhs;\
    return result;\
  }\
  pArray pArray::operator oper(const double &rhs) const {\
    pArray result(*this);\
    result opers rhs;\
    return result;\
  }
OPERFUNC(+, +=, NOT_DIVIDE, NOT_POW)
OPERFUNC(-, -=, NOT_DIVIDE, NOT_POW)
OPERFUNC(*, *=, NOT_DIVIDE, NOT_POW)
OPERFUNC(/, /=, DIVIDE, NOT_POW)
OPERFUNC(^, ^=, DIVIDE, POW)

#undef NOT_DIVIDE
#undef DIVIDE
#undef NOT_POW
#undef POW
#undef OPERFUNC
//**********************************************************************
ostream & operator<<(ostream & out, const pArray & ref) {
  out<<"[pArray: Length="<<ref.GetLength()<<"]"<<endl;
  out<<"Name: "<<ref.GetName()<<endl;
  out<<"Unit: "<<ref.GetUnit()<<endl;
  out<<"Comments: "<<ref.GetComments()<<endl;
  out<<scientific;
  for(int i=0; i<ref.GetLength(); i++) {
    out<<ref.a[i]<<endl;
  }
  return out;
}
