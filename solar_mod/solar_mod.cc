#include<cmath>
#include"interp.h"
#include"solar_mod.h"

using std::abs;
using std::cout;
using std::endl;
using std::string;

#define m0A 0 == A ? 0.511e-3 : 0.9382

solar_mod::solar_mod() : pflag(false), nA(1), A(0), Z(0) {};
solar_mod::solar_mod(int A_, int Z_, bool pflag_): pflag(pflag_), m0(m0A), nA(0 == A_ ? 1 : A_), A(A_), Z(Z_) {}

solar_mod::solar_mod(int A_, int Z_): pflag(false), m0(m0A), nA(0 == A_ ? 1 : A_), A(A_), Z(Z_) {}

int solar_mod::ini(int A_, int Z_, double phi_, bool pflag_) {
  nA = 0 == A_ ? 1 : A_;
  A = A_;
  Z = Z_;
  m0 = (m0A);
  phi_ini(phi_);
  pflag = pflag_;
  return 0;
}
int solar_mod::ini(int A_, int Z_, double phi_) {
  return ini(A_, Z_, phi_, false);
}

void solar_mod::rigidity_to_ekin(spectrum& spec) {
  for (unsigned i = 0; i < spec.E.size(); i++) {
    double momentum = spec.E[i] * abs(Z);
    double energy = sqrt(momentum * momentum + nA * m0 * nA * m0);
    spec.E[i] = (energy - m0) / nA; // assign Ekin_per
    spec.F[i] = spec.F[i] * energy / momentum * nA / abs(Z); // dNdEkinper = dNdR * E / p * A / Z
  }
}
void solar_mod::ekin_to_rigidity(spectrum& spec) {
  for (unsigned i = 0; i < spec.E.size(); i++) {
    double energy = (spec.E[i] + m0) * nA;
    double momentum = sqrt(energy * energy - nA * m0 * nA * m0);
    spec.E[i] = momentum / abs(Z); // assign R
    spec.F[i] = spec.F[i] * momentum / energy * abs(Z) / nA; // dNdR = dNdEkinper * p / E * Z / A
  }
}
int solar_mod::mod(spectrum &spec, double phi_, const string &type) {
  if (phi_ >= 0) phi_ini(phi_);

  if (type != "rigidity" && type != "ekin") {
    cout << "solar_mod::mod::Error::the type you specified must be \"rigidity\" or \"ekin\"" << endl;
    exit(0);
  }

  if (type == "rigidity") rigidity_to_ekin(spec);

  spectrum spec_tmp(spec);
  int result = mod(spec_tmp, spec);

  if (type == "rigidity") ekin_to_rigidity(spec);

  return result;
}

int solar_mod::mod(pArray &E_, pArray &F_, double phi_, const string &type) {
  spectrum spec(E_, F_);

  int result = mod(spec, phi_, type);

  E_.SetValues(spec.E);
  F_.SetValues(spec.F);
  return result;
}

int solar_mod::mod(const spectrum &spec_o, spectrum &spec_t, double phi_) {
  cout << "solar_mod::mod::The modulating function is not called" << endl;
  return 0;
}

int solar_mod::phi_ini(double phi_) {
  cout << "solar_mod::phi_ini::The phi is not changed" << endl;
  return 0;
}
