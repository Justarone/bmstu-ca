#include <stdio.h>
#include <stdlib.h>

#include "include/algorithms.h"
#include "include/iomodule.h"
#include "include/struct.h"
#include "include/constants.h"


int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    data_t data = { 0 };
    int rc;

    if (argc > 1)
        rc = read_data(&data, argv[1]);
    else
        rc = read_data(&data, FILENAME);

    if (rc)
        return rc;

    result_processing(&data);

    free(data.divided_sums);
    for (int i = 0; i < COORDINATES; i++)
        free(data.table[i]);
    free(data.table);
    return 0;
}
