#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// Flags
// #define DEBUG
// #define POL_PRINT
#define TABLE_PRINT

enum ERRORS_T { OK, FILE_ERROR, READ_ERROR, POL_DEG_ERROR, EXTRAPOLATION_ERROR, NO_ORDER_ERROR };

#define FALSE 0
#define TRUE 1

#define NORMAL 0
#define REVERSED 1
#define NO_CACHE -1

#define MAX_ONE_ARG 100
#define ONE_POINT 3
#define X 0
#define Y 1
#define Z 2

#define READED 1
#define COORDINATES 2
#define INIT_SIZE 2

#define REV_INT_VALUE 0
#define OUTPUT stdout
#define INPUT stdin
#define FILENAME "test/data/data_01.txt"

#endif
