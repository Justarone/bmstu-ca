#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "struct.h"

double half_division(data_t *const data);
// `mode` should be `REVERSED` or `NORMAL`
double interpolation(data_t *const data, const double argument,
                     const int mode, const int cache_usage);

#endif
