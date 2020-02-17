#include <stdio.h>
#include <stdlib.h>

#include "../include/algorithms.h"
#include "../include/iomodule.h"
#include "../include/struct.h"
#include "../include/constants.h"


int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    data_t data = { 0 };
    int rc;

    if (argc > 1)
        rc = read_data(&data, argv[1], argc < 3);
    else
        rc = read_data(&data, FILENAME, argc < 3);

    if (rc)
        return rc;

    enum ERRORS_T error = data_check(&data);
    switch(error)
    {
        case POL_DEG_ERROR:
            fprintf(OUTPUT,
                    "Incorrect polinomial degree: there is no enough points to solve this.\n");
            return POL_DEG_ERROR;

        case EXTRAPOLATION_ERROR:
            fprintf(OUTPUT, "Extrapolation error.\n"); 
            return EXTRAPOLATION_ERROR;

        case NO_ROOT_ERROR:
            fprintf(OUTPUT, "Function doesn't cross 0 or function is not monotonous.\n");
            return NO_ROOT_ERROR;

        case NO_ORDER_ERROR:
            fprintf(OUTPUT, "Points in table are not ordered or function is not monotonous\n");
            return NO_ORDER_ERROR;

        default:
            break;
    }

    result_processing(&data);

    /*free(data.divided_sums);*/
    /*for (int i = 0; i < COORDINATES; i++)*/
        /*free(data.table[i]);*/
    /*free(data.table);*/
    /*return 0;*/
}
