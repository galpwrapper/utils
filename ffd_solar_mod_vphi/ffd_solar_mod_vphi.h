#ifndef _FFD_SOLAR_MOD_VPHI_H
#define _FFD_SOLAR_MOD_VPHI_H
/*********************************************************************
 solar modulation with phi (GV) of CRs in force field approximation
 Reference: Gleeson & Axford, 1968, ApJ, 154, 1011
 E and E_mod are kinetic energy per nucleon
 From solar_mod.f file.
 *********************************************************************/
#include <functional>

#include"solar_mod.h"

class ffd_solar_mod_vphi : public solar_mod {
private:
  double getphi() const;
  int domod(const spectrum &spec_o, spectrum &spec_t);
  inline double vphi(double Ekin) const { return phi_func(sqrt((Ekin + m0) * (Ekin + m0) - m0 * m0) * nA / abs(double(Z))) * abs(double(Z)) / nA; }
  int ini(int A_, int Z_, const std::function<double(double)>& phi_, bool pflag_);
  int ini(int A_, int Z_, bool pflag_);

public:
  std::function<double(double)> phi_func;

  ffd_solar_mod_vphi();
  ffd_solar_mod_vphi(int A_, int Z_, const std::function<double(double)>& phi_, bool pflag_ = false);
};
#endif // for #ifndef _FFD_SOLAR_MOD_VPHI_H
