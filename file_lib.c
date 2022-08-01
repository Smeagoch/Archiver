#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "file_lib.h"

symbol *out_file(char *file_name, int *size)
{
    FILE *out_file = fopen(file_name, "rb");
    if (out_file == NULL)
    {
        return 0;   
    }
    fseek(out_file, 0, SEEK_END);
    int fsize = ftell(out_file);
    rewind(out_file);

    symbol *sym = (symbol *) malloc(sizeof(symbol));
    unsigned char *ch = (unsigned char*) malloc(fsize * sizeof(unsigned char));

    fread(ch, 1, fsize, out_file);
    for (int i = 0; i < fsize; i++)
    {
        if (i == 0)
        {
            *size = *size + 1;
            sym->ch = ch[i];
            sym->freq = (float) 1 / fsize;
            sym->left = NULL;
            sym->right = NULL;
        }
        else
        {
            for (int j = 0; j < *size; j++)
            {
                if (sym[j].ch == ch[i])
                {
                    sym[j].freq =  (sym[j].freq * fsize + 1) / fsize;
                    break;
                }
                if (j == *size - 1)
                {
                    *size = *size + 1;
                    sym = (symbol *) realloc(sym, *size * sizeof(symbol)); 
                    sym[*size - 1].ch = ch[i];
                    sym[*size - 1].freq = (float) 1 / fsize;
                    sym[*size - 1].left = NULL;
                    sym[*size - 1].right = NULL;
                    break;
                }
            }
        }
    }
    free(ch);
    fclose(out_file);
    return sym;
}