#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NEW_TIPES_H
#define NEW_TIPES_H

typedef struct symbol
{
    unsigned char ch; // symbol
    float freq; // the frequency with which the character occurs in the file
    char code[255]; // new symbol encoding

    /* addresses for tree formation */
    struct symbol *left;
    struct symbol *right;
}symbol;

#endif /* NEW_TYPES_H */