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

union code
{
    unsigned char sym_to_write;

    struct byte
    {
        unsigned b0 : 1;
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
    }byte;
};


#endif /* NEW_TYPES_H */