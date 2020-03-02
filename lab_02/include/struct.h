#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "constants.h"

typedef struct data_t
{
    double x[2];
    unsigned n[2];
    double table[MAX_ONE_ARG][MAX_ONE_ARG][ONE_POINT];
    int size[2];
} data_t;

#endif
