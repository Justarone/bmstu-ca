#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "struct.h"
#include "constants.h"

void count_div_sums(data_t *const data, const int section_start, const int mode);
int find_section(const data_t *const data, const double argument, const int mode);
enum ERRORS_T data_check(const data_t *const data);
double half_division(data_t *const data);
// `mode` should be `REVERSED` or `NORMAL`
double interpolation(data_t *const data, const double argument,
                     const int mode, const int cache_usage);

#endif
