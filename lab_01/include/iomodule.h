#ifndef _IOMODULE_H_
#define _IOMODULE_H_

#include "struct.h"

int read_data(data_t *const data, const char *const filename, const int user_flag);
void result_processing(data_t *const data);

#endif
