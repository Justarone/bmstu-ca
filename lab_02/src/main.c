#include <stdio.h>
#include <stdlib.h>

#include "../include/algorithms.h"
#include "../include/iomodule.h"
#include "../include/struct.h"
#include "../include/constants.h"


int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    data_t data;
    int rc;


    if (argc > 1)
        rc = read_data(&data, argv[1]);
    else
        rc = read_data(&data, FILENAME);

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

        case NO_ORDER_ERROR:
            fprintf(OUTPUT, "Points in table are not ordered or function is not monotonous\n");
            return NO_ORDER_ERROR;

        default:
            break;
    }

    result_processing(&data);
}
