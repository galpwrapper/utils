#ifndef _FFD_SOLAR_MOD_H
#define _FFD_SOLAR_MOD_H
/*********************************************************************
 solar modulation with phi (GV) of CRs in force field approximation
 Reference: Gleeson & Axford, 1968, ApJ, 154, 1011
 E and E_mod are kinetic energy per nucleon
 From solar_mod.f file.
 *********************************************************************/
#include"solar_mod.h"

class ffd_solar_mod : public solar_mod {
private:
  double getphi() const;
  int phi_ini(double phi_);
  int domod(const spectrum &spec_o, spectrum &spec_t);

public:
  double phi;
  ffd_solar_mod();
  ffd_solar_mod(int A_, int Z_, double phi_, bool pflag_ = false);
};
#endif // for #ifndef _FFD_SOLAR_MOD_H
