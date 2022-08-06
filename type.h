#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NEW_TIPES_H
#define NEW_TIPES_H

typedef struct symbol
{
    unsigned char ch;
    float freq;
    char code[255];
    struct symbol *left;
    struct symbol *right;
}symbol;

#endif /* NEW_TYPES_H */