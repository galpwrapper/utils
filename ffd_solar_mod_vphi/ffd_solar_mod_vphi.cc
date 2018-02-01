#include<cmath>
#include<sstream>
#include<iomanip>
#include"interp.h"
#include"ffd_solar_mod_vphi.h"
#include"root_finding.h"

using namespace std;

#define m0A 0 == A_ ? 0.511e-3 : 0.9382

int ffd_solar_mod_vphi::ini(int A_, int Z_, bool pflag_)
{
  nA = 0 == A_ ? 1 : A_;
  A = A_;
  Z = Z_;
  m0 = (m0A);
  pflag = pflag_;
}

int ffd_solar_mod_vphi::ini(int A_, int Z_, const function<double(double)>& phi_, bool pflag_)
{
  ffd_solar_mod_vphi::ini(A_, Z_, pflag_);
  phi_func = phi_;
}

ffd_solar_mod_vphi::ffd_solar_mod_vphi() { ffd_solar_mod_vphi::ini(0, 0, false); };
ffd_solar_mod_vphi::ffd_solar_mod_vphi(int A_, int Z_, const function<double(double)>& phi_, bool pflag_) {
    ini(A_, Z_, phi_, pflag_);
}

int ffd_solar_mod_vphi::domod(const spectrum &spec_o, spectrum &spec_t) {
  interp intp_ori(spec_o);

  if (vphi(0) >= 0) { //modulation
    for (unsigned i = 0; i < spec_t.E.size(); i++) {
      spec_t.F[i] = intp_ori.lnask_check(spec_t.E[i] + vphi(spec_t.E[i]))
                    * spec_t.E[i] * (spec_t.E[i] + 2 * m0)
                    / ((spec_t.E[i] + vphi(spec_t.E[i])) * (spec_t.E[i] + vphi(spec_t.E[i]) + 2 * m0));
    }

  } else { // demodulation
    spectrum temp;
    temp.E.clear(); temp.E.reserve(spec_o.E.size());
    temp.F.clear(); temp.F.reserve(spec_o.F.size());
    double ekin_lis_min = 0;
    for (unsigned i = 0; i < spec_o.E.size(); i++) {
      double ekin_earth = spec_o.E[i];
      double ekin_lis = ekin_earth - vphi(ekin_earth);

      temp.E.push_back(ekin_lis);
      temp.F.push_back(intp_ori.lnask_check(ekin_earth)
                      * ekin_lis * (ekin_lis + 2 * m0)
                      / (ekin_earth * (ekin_earth + 2 * m0)));
    }
    for (int i = temp.E.size() - 1; i > 0; i--)
      if (temp.E[i] <= temp.E[i - 1]) temp.del_p(i - 1);

    interp intp_temp(temp);
    for (unsigned i = 0; i < spec_t.E.size(); i++)
      spec_t.F[i] = intp_temp.lnask_check(spec_t.E[i]);

    //while (spec_t.E.size() > 0 && spec_t.F[0] == 0)
    //  spec_t.del_p(0);

    //if (spec_t.E.size() == 0) cout << "All these flux should not come from the outside Galaxy" << endl;
  }

  if (pflag) {
    cout << setiosflags(ios::scientific) << setprecision(6);
    for (unsigned i = 0; i < spec_t.E.size(); i++)
      cout << spec_t.E[i] << " " << intp_ori.lnask_check(spec_t.E[i]) << " " << spec_t.F[i] << endl;
  }

  return 0;
}

double ffd_solar_mod_vphi::getphi() const {
  return phi_func(0);
}
