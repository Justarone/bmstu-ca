#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct data_t
{
    double acc;
    double abs_acc;
    double x;
    unsigned n;
    double **table;
    unsigned size;
    unsigned mem_size;
    double *divided_sums;
    char is_cached;
    int cached_for;
} data_t;

#endif
