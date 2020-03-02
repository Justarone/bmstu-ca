#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "struct.h"
#include "constants.h"

enum ERRORS_T data_check(const data_t *const data);
double interpolation(double **const points, const int size, const int deg, const double arg, 
        const int mode);
double multi_interpolation(data_t *const data);

#endif
