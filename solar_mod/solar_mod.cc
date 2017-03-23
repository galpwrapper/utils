#include<cmath>
#include"interp.h"
#include"solar_mod.h"

using std::abs;
using std::cout;
using std::endl;
using std::string;

#define m0A 0 == A_ ? 0.511e-3 : 0.9382

int solar_mod::ini(int A_, int Z_, double phi_, bool pflag_) {
  nA = 0 == A_ ? 1 : A_;
  A = A_;
  Z = Z_;
  m0 = (m0A);
  phi_ini(phi_);
  pflag = pflag_;
  return 0;
}

int solar_mod::mod(spectrum &spec, double phi_, const string &type) {
  spectrum spec_tmp(spec);
  return mod(spec_tmp, spec, phi_, type);
}

int solar_mod::mod(pArray &E_, pArray &F_, double phi_, const string &type) {
  spectrum spec(E_, F_);

  int result = mod(spec, phi_, type);

  E_.SetValues(spec.E);
  F_.SetValues(spec.F);
  return result;
}

void solar_mod::rigidity_to_ekin(spectrum& spec) {
  for (unsigned i = 0; i < spec.E.size(); i++) {
    double momentum = spec.E[i] * abs(Z);
    double energy = sqrt(momentum * momentum + nA * m0 * nA * m0);
    spec.E[i] = energy / nA - m0; // assign Ekin_per
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
int solar_mod::mod(const spectrum &spec_o, spectrum &spec_t, double phi_, const string &type) {
  if (phi_ >= 0) phi_ini(phi_);

  if (type != "rigidity" && type != "ekin") {
    cout << "solar_mod::mod::Error::the type you specified must be \"rigidity\" or \"ekin\"" << endl;
    exit(0);
  }

  if (pflag) {
    cout << "#Solar modulation with A = " << A << "  Z = " << Z << "  effective phi = " << phi() << "  m0 = " << m0 << endl;
    cout << "#E   (F_before_modulation)   F_after_modulation" << endl;
  }

  spec_t = spec_o;
  if (type == "rigidity") {

    rigidity_to_ekin(spec_t);
    spectrum spec_o_tmp(spec_t);

    int result = domod(spec_o_tmp, spec_t);

    ekin_to_rigidity(spec_t);

    return result;
  }

  return domod(spec_o, spec_t);
}

int solar_mod::domod(const spectrum &spec_o, spectrum &spec_t) {
  cout << "solar_mod::mod::The modulating function is not called" << endl;
  return 0;
}

int solar_mod::phi_ini(double phi_) {
  cout << "solar_mod::phi_ini::The phi is not changed" << endl;
  return 0;
}

double solar_mod::getphi() const {
  cout << "solar_mod::phi::No phi is available" << endl;
  return 0;
}

double solar_mod::phi() const {
  return getphi();
}
