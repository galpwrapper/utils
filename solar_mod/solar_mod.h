#ifndef _SOLAR_MOD_H
#define _SOLAR_MOD_H
/*********************************************************************
 solar modulation with phi (GV) of CRs
 This is a shell to both the force field approximation and a spherical
 symmetric method.

 Reference: Gleeson & Axford, 1968, ApJ, 154, 1011
 E and E_mod are kinetic energy per nucleon
 From solar_mod.f file.
 *********************************************************************/
#include"spectrum.h"
#include"pArray.h"
class solar_mod {
protected:
  bool pflag;
  double m0;

  virtual double getphi() const;
  virtual int phi_ini(double phi_);
  virtual int domod(const spectrum &spec_o, spectrum &spec_t);

public:
  int nA, A, Z;

  void rigidity_to_ekin(spectrum& spec);
  void ekin_to_rigidity(spectrum& spec);

  int ini(int A_, int Z_, double phi_, bool pflag_ = false);

  int mod(spectrum &spec, double phi_ = -1, const std::string &type = "ekin");
  int mod(pArray &E_, pArray &F_, double phi_ = -1, const std::string &type = "ekin");
  int mod(const spectrum &spec_o, spectrum &spec_t, double phi_ = -1, const std::string &type = "ekin");

  double phi() const;
};
#endif // for #ifndef _SOLAR_MOD_H
