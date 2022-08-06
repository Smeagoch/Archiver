#include "type.h"
#ifndef MATH_LIB_H
#define MATH_LIB_H

void descen_sort(symbol *sym, int size);

symbol *make_tree(symbol *sym, int *size, symbol *branch, int nbranch);

void coder_tree(symbol *tree_begin, int nsymbol, int* left_right, int passage);

#endif /* MATH_LIB_H */