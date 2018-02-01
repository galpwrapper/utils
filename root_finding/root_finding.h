#ifndef _ROOT_FINDING_H
#define _ROOT_FINDING_H

#include <functional>

// Search for root between x0 and x1
double ridders_method(const std::function<double(const double)>& func, double x0, double x1);

#endif // for #ifndef _ROOT_FINDING_H
