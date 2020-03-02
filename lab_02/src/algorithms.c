#include <stdio.h>
#include <stdlib.h>


#include "../include/algorithms.h"

#define ABS(X) X > 0 ? X : -X

enum ERRORS_T data_check(const data_t *const data)
{
    if (data->n[Y] > data->size[Y] || data->n[X] > data->size[X])
        return POL_DEG_ERROR;

    double sign_x = (data->table[1][0][X] > data->table[0][0][X]) - 0.5;
    double sign_y = (data->table[0][1][Y] > data->table[0][0][Y]) - 0.5;
    if ((data->x[X] - data->table[0][0][X]) * sign_x < 0 ||
            (data->x[X] - data->table[data->size[X] - 1][0][X]) * sign_x > 0)
        return EXTRAPOLATION_ERROR;

    if ((data->x[Y] - data->table[0][0][Y]) * sign_y < 0 ||
            (data->x[Y] - data->table[0][data->size[Y] - 1][Y]) * sign_y > 0)
        return EXTRAPOLATION_ERROR;


    for (int i = 0; i < data->size[Y] - 1; i++)
    {
        // once we check values to have "value grid"
        for (int j = 0; j < data->size[X] - 1; j++)
            if (data->table[j][i][Y] != data->table[j + 1][i][Y] || data->table[j][i][X] !=
                    data->table[j][i + 1][X])
                return NO_ORDER_ERROR;

        if ((data->table[0][i + 1][Y] - data->table[0][i][Y]) * sign_y < 0)
            return NO_ORDER_ERROR;
    }

    for (int i = 0; i < data->size[X] - 1; i++)
    {
        if ((data->table[i + 1][0][X] - data->table[i][0][X]) * sign_x < 0)
            return NO_ORDER_ERROR;
    }

    return OK;
}


static int find_section(double **const points, const int size, const int deg, const double arg,
        const int mode)
{
    double sign = (points[0][mode] < points[1][mode]) - 0.5;
    int index = 0;
    // explanation for increasing sequence:
    // until we didn't meet number, which is bigger - we keep searching,
    // else - we should be before it.
    while (index < size && (arg - points[index][mode]) * sign > 0)
        index++;

    if (index == 0 || index == size)
    {
        index -= deg;
        fprintf(OUTPUT, "Extrapolation!\n");
        return index > 0 ? index : 0;
    }
    
    int end_diff = deg / 2 - (1 - (1 & deg)) - (size - index - 1);
    //             half sector   not `even` sector     place left behind

    if (end_diff < 0)
        end_diff = 0;

    index -= deg / 2 + end_diff;
    return index > 0 ? index : 0; 
}


static double *count_div_sums(double **const points, const int deg,
        const int section_start, const int mode)
{
    double *div_sums = malloc(deg * (deg - 1) / 2 * sizeof(double));
    for (int i = section_start; i < section_start + deg - 1; i++)
        div_sums[i - section_start] = (points[i][Z] - points[i + 1][Z]) /
            (points[i][mode] - points[i + 1][mode]);

    double *cur_elem = div_sums + deg - 1;
    double *sum_ptr = div_sums;

    for (int i = 1; i < deg - 1; i++)
    {
        for (int j = 0; j < deg - i - 1; j++)
        {
            *cur_elem = (*sum_ptr - *(sum_ptr + 1)) / 
                (points[section_start + j][mode] - points[section_start + j + 1 + i][mode]);
            cur_elem++, sum_ptr++;
        }
        sum_ptr++;
    } 
    /*printf("\n\ndiv_sums!:\n\n");*/
    /*for (int i = 0; i < deg * (deg - 1) / 2; i++)*/
        /*printf("%.2lf,   ", div_sums[i]);*/
    /*printf("\n\n");*/
    return div_sums;
}


static double polynomial_value(double **const points, const int section_start,
        const int deg, const double arg, const int mode, double *div_sums)
{
    double multi = 1;
    double summary = points[section_start][Z];
    int index = 0;

    for (int i = 0; i < deg - 1; i++)
    {
        multi *= (arg - points[section_start + i][mode]);
        summary += multi * div_sums[index];
        index += deg - i - 1;
    }
    return summary;
}


double interpolation(double **const points, const int size, const int deg, const double arg,
        const int mode)
{
    int section_start = find_section(points, size, deg, arg, mode);
    double *div_sums = count_div_sums(points, deg, section_start, mode);
    double result = polynomial_value(points, section_start, deg, arg, mode, div_sums);
    return result;
}


double multi_interpolation(data_t *const data)
{
    double *buffer[data->size[X]];
    for (int i = 0; i < data->size[X]; i++)
        buffer[i] = data->table[i][0];
    int section_start = find_section(buffer, data->size[X], data->n[X], data->x[X], X);
    
    double **y_res = malloc(data->n[X] * sizeof(double *));
    for (int i = 0; i < data->size[X]; i++)
        y_res[i] = malloc(ONE_POINT * sizeof(double));

    double **points = malloc(data->size[Y] * sizeof(double *));
    for (int i = 0; i < data->size[Y]; i++)
        points[i] = malloc(ONE_POINT * sizeof(double));

    for (int i = section_start; i < section_start + data->n[X]; i++)
    {
        for (int j = 0; j < data->size[Y]; j++)
        {
            points[j][X] = data->table[i][0][X];
            points[j][Y] = data->table[i][j][Y];
            points[j][Z] = data->table[i][j][Z];
        }
        /*printf("Row is:\n");*/
        /*for (int k = 0; k < data->size[Y]; k++)*/
            /*printf("%.2lf, %.2lf, %.2lf;    ", points[k][X], points[k][Y], points[k][Z]);*/
        /*printf("\nsection_start: %d\n", find_section(points, data->size[Y],*/
                /*data->n[Y], data->x[Y], Y));*/

        y_res[i - section_start][Z] = interpolation(points, data->size[Y],
                data->n[Y], data->x[Y], Y);
        /*printf("\n\nresult is: %.2lf\n\n", y_res[i - section_start][Z]);*/
        y_res[i - section_start][X] = data->table[i][0][X];
        y_res[i - section_start][Y] = data->x[Y];
    }

    double result = interpolation(y_res, data->n[X], data->n[X], data->x[X], X);

    return result;
}
