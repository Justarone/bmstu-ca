#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/iomodule.h"
#include "../include/struct.h"
#include "../include/constants.h"
#include "../include/algorithms.h"


int read_data(data_t *const data, const char *const filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(OUTPUT, "Something went wrong with file...");
        return FILE_ERROR;
    }

    // read_data
    fscanf(f, "%d%d", data->size, data->size + 1);
    for (int i = 0; i < data->size[X]; i++)
        for (int j = 0; j < data->size[Y]; j++)
        {
            if (fscanf(f, "%lf%lf%lf", &data->table[i][j][X], &data->table[i][j][Y], 
                        &data->table[i][j][Z]) != ONE_POINT)
                return FILE_ERROR;
        }

    // if table successfully read:
    for (int i = 0; i < data->size[X]; i++)
    {
        for (int j = 0; j < data->size[Y]; j++)
            fprintf(OUTPUT, "(%.2lf; %.2lf; %.2lf);  ", data->table[i][j][X], data->table[i][j][Y],
                    data->table[i][j][Z]);
        fprintf(OUTPUT, "\n");
    }



    fclose(f);
    fprintf(OUTPUT, "Data from file successfully readed!\n");


    fprintf(OUTPUT, "Enter x: ");
    fscanf(INPUT, "%lf", &data->x[X]);

    fprintf(OUTPUT, "Enter y: ");
    fscanf(INPUT, "%lf", &data->x[Y]);


    fprintf(OUTPUT, "Enter x polynomial degree: ");
    fscanf(INPUT,"%u", &data->n[X]);

    fprintf(OUTPUT, "Enter y polynomial degree: ");
    fscanf(INPUT,"%u", &data->n[Y]);
    data->n[X]++; 
    data->n[Y]++; 
    fprintf(OUTPUT, "\n\n");

    return OK;
}


void result_processing(data_t *const data)
{
    fprintf(OUTPUT, "Interpolation result:\ny = f(%.3lf, %.3lf) = %lf\n\n", data->x[X],
            data->x[Y], multi_interpolation(data));
}
