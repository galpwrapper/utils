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
                 Length(0) {
  init();
}
pArray::pArray(std::string _Name,
               int _Length,
               std::string _Unit,
               std::string _Comments ):Name(_Name),
                                       Unit(_Unit),
                                       Comments(_Comments),
                                       Length(_Length) {
  init();
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
void pArray::SetName(std::string _Name) {
  Name = _Name;
}
void pArray::SetUnit(std::string _Unit) {
  Unit = _Unit;
}
void pArray::SetComments(std::string _Comments) {
  Comments = _Comments;
}
void pArray::SetValues(const vector <double> &v) {
  Length = v.size();
  delete []a;
  a = new double[Length];
  copy(&(v[0]), &(v[0]) + Length, a);
}
void pArray::SetValues(const pArray &arr) {
  Length = arr.GetLength();
  delete []a;
  a = new double[Length];
  copy(arr.a, arr.a + Length, a);
}
void pArray::SetValues(double *v, int _Length) {
  Length = _Length;
  delete []a;
  a = new double[Length];
  copy(v, v + Length, a);
}

void pArray::resize(int _Length) {
  Length = _Length;

  delete []a;
  init();
}
void pArray::init() {
  if(Length == 0)
    a = NULL;
  else {
    a = new double[Length];
    memset(a, 0, Length*sizeof(double));
  }
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
#define CK_UNIT true
#define NOT_CK_UNIT  false
#define NOT_DIVIDE(lhs, ope, rhs, res) res = lhs ope rhs
#define DIVIDE(lhs, ope, rhs, res)\
  if(rhs == 0) res=0;\
  else res = lhs ope rhs

#define NOT_POW(div_or_not, lhs, ope, rhs, res)\
  div_or_not(lhs, ope, rhs, res)
#define POW(div_or_not, lhs, ope, rhs, res)\
  res = pow(lhs, rhs)

#define OPERFUNC(oper, opers, div_or_not, pow_or_not, ck_unit )\
  pArray operator oper(const double &lhs, const pArray &rhs) {\
    pArray result(rhs);\
    for(int i=0; i<result.GetLength(); i++) {\
      pow_or_not(div_or_not, lhs, oper, rhs.a[i], result.a[i]);\
    }\
    return result;\
  }\
  pArray & pArray::operator opers(const pArray &rhs) {\
    if(Length != rhs.GetLength() || (ck_unit && Unit != rhs.GetUnit())) {\
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
OPERFUNC(+, +=, NOT_DIVIDE, NOT_POW, CK_UNIT)
OPERFUNC(-, -=, NOT_DIVIDE, NOT_POW, CK_UNIT)
OPERFUNC(*, *=, NOT_DIVIDE, NOT_POW, NOT_CK_UNIT)
OPERFUNC(/, /=, DIVIDE, NOT_POW, NOT_CK_UNIT)
OPERFUNC(^, ^=, DIVIDE, POW, NOT_CK_UNIT)

#undef NOT_DIVIDE
#undef DIVIDE
#undef NOT_POW
#undef POW
#undef OPERFUNC
//**********************************************************************
bool operator!=(const pArray &lhs, const pArray &rhs) {
  if (lhs.GetName() != rhs.GetName() ||
      lhs.GetUnit() != rhs.GetUnit() ||
      lhs.GetComments() != rhs.GetComments() ||
      lhs.GetLength() != rhs.GetLength()) return true;

  for (unsigned i = 0; i < lhs.GetLength(); i++)
    if (lhs.a[i] != rhs.a[i]) return true;

  return false;
}
bool operator==(const pArray &lhs, const pArray &rhs) {
  return !(lhs != rhs);
}

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
