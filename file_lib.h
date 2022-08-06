#include "type.h"

#ifndef FILE_LIB_H
#define FILE_LIB_H

symbol *out_file(char *file_name, int *size);

void in_file(symbol *sym, int size, char *file_name);

#endif /* FILE_LIB_H */