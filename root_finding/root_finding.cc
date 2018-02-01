#include <cmath>
#include <iostream>

#include "root_finding.h"

using namespace std;

double ridders_method(const function<double(const double)>& func, double x0, double x1) {
  double low = fmin(x0, x1),
         up = fmax(x0, x1),
         point,
         flow = func(low),
         fup = func(up),
         fpoint;

  if (flow * fup > 0) {
    cerr << "Ridder's method: Could not find a root for " << x0 << " " << x1 << " in the same side" << endl;
    exit(1);
  }
  if (x1 == 0 && x0 == 0) return 0;

  while (true) {
    double mid = (low + up) / 2,
      fmid = func(mid);
    point = mid + (mid - low) * (flow < 0 ? -1 : 1) * fmid / sqrt(fmid * fmid - flow * fup);
    fpoint = func(point);
    if (fpoint == 0 || fpoint == flow || fpoint == fup) break;

    if (fpoint * flow < 0) {
      up = point;
      fup = fpoint;
    } else {
      low = point;
      flow = fpoint;
    }
  }

  return point;
}
