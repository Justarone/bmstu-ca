#include <stdio.h>
#include <stdlib.h>

#include "../include/iomodule.h"
#include "../include/struct.h"
#include "../include/constants.h"
#include "../include/algorithms.h"


int read_data(data_t *const data, const char *const filename, const int user_flag)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(OUTPUT, "Something went wrong with file...");
        return FILE_ERROR;
    }

    // Table init.

    data->table = (double **)malloc(COORDINATES * sizeof(double *));
    if (!data->table)
    {
        fprintf(OUTPUT, "Something went wrong with memory allocation...");
        fclose(f);
        return ALLOC_ERROR;
    }

    for (int i = 0; i < COORDINATES; i++)
    {
        data->table[i] = (double *)malloc(INIT_SIZE * sizeof(double));

        if (!data->table[i])
        {
            for (int j = i - 1; j >= 0; j--)
                free(data->table[j]);

            free(data->table);
            fclose(f);
            fprintf(OUTPUT, "Something went wrong with memory allocation...");
            return ALLOC_ERROR;
        }
    }
    data->mem_size = INIT_SIZE;

    // Fill table from file at first
    double buf[COORDINATES];
    while (fscanf(f, "%lf%lf", buf, buf + 1) == READED * 2)
    {
        // If we reached memory limit --> realloc.
        if (data->size == data->mem_size)
        {
            for (int i = 0; i < COORDINATES; i++)
            {
                double *tmp = (double *)realloc(data->table[i],
                        data->mem_size * sizeof(double) * 2);
                if (!tmp)
                {
                    for (int j = 0; j < COORDINATES; j++)
                        free(data->table[j]);
                    free(data->table);
                    fclose(f);
                    fprintf(OUTPUT, "Something went wrong with memory allocation...");
                    return ALLOC_ERROR;
                }
                data->table[i] = tmp;
            } 
            data->mem_size *= 2;
        }

        // Fill table with readed data.
        for (int i = 0; i < COORDINATES; i++)
            data->table[i][data->size] = buf[i];
        data->size++;
    }
    fclose(f);
    fprintf(OUTPUT, "Data from file successfully readed!\n");


    if (user_flag)
        fprintf(OUTPUT, "Enter x: ");
    fscanf(INPUT, "%lf", &data->x);
    if (!user_flag)
        fprintf(OUTPUT, "x = %g;\n", data->x);

    if (user_flag)
        fprintf(OUTPUT, "Enter accuracy (for half division method): ");
    fscanf(INPUT, "%lf", &data->acc);
    if (!user_flag)
        fprintf(OUTPUT, "Accuracy = %g;\n", data->acc);

    if (user_flag)
        fprintf(OUTPUT, "Enter absolute accuracy (for half division method):");
    fscanf(INPUT,"%lf", &data->abs_acc);
    if (!user_flag)
        fprintf(OUTPUT, "Absolute accuracy = %g;\n", data->abs_acc);

    if (user_flag)
        fprintf(OUTPUT, "Enter polynomial degree: ");
    fscanf(INPUT,"%u", &data->n);
    if (!user_flag)
        fprintf(OUTPUT, "Polynomial degree = %d;\n", data->n);

    data->n++; // cause data n - number of points (more than polynomial degree).
    fprintf(OUTPUT, "\n\n");

    // Init divided_sums array.
    data->divided_sums = (double *)malloc((data->n - 1) * data->n / 2 * sizeof(double)); 
    if (!data->divided_sums)
    {
        fprintf(OUTPUT, "Something went wrong with memory allocation...");
        for (int i = 0; i < COORDINATES; i++)
            free(data->table[i]);
        free(data->table);

        return ALLOC_ERROR;
    }

    data->is_cached = NO_CACHE;
    data->cached_for = NO_CACHE;
    return OK;
}


void print_polynomial(const data_t *const data, const int mode)
{
    int section_start = find_section(data, data->x, mode);
    fprintf(OUTPUT, "Pn(x) = %.3lf", data->table[1 ^ mode][section_start]);
    int index = 0;

    for (int i = 0; i < data->n - 1; i++)
    {
        fprintf(OUTPUT, " + ");
        fprintf(OUTPUT, "(x - %.3lf)", data->table[0 ^ mode][section_start]);
        for (int j = 1; j <= i; j++)
            fprintf(OUTPUT, " * (x - %.3lf)", data->table[0 ^ mode][section_start + j]);
        fprintf(OUTPUT, " * %.3lf", data->divided_sums[index]);
        index += data->n - i - 1;
    }
    fprintf(OUTPUT, "\n\n");
}


void result_processing(data_t *const data)
{
    fprintf(OUTPUT, "Interpolation result:\ny = f(%.3lf) = %lf\n\n", data->x,
            interpolation(data, data->x, NORMAL, FALSE));

#ifdef POL_PRINT
    print_polynomial(data, NORMAL);
#endif

    fprintf(OUTPUT, "Reversed interpolation (root):\ny = f(%.3lf) = %lf\n\n",
            interpolation(data, REV_INT_VALUE, REVERSED, FALSE), (double) REV_INT_VALUE);

    if (data->size > 1 && data->table[1][0] * data->table[1][data->size - 1] < 0)
        fprintf(OUTPUT, "Half division method:\nRoot: %.5lf;\nAccuracy: %.5lf\n\n",
                half_division(data), data->acc);
    else
        fprintf(OUTPUT,
                "Can't find solution: need different signs on the boundaries of function.");
}
