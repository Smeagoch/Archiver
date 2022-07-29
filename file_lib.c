#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "file_lib.h"

symbol *out_file (char *file_name)
{
    FILE *out_file = fopen(file_name, "rb");
    if (out_file == NULL)
    {
        return NULL;   
    }
    fseek(out_file, 0, SEEK_END);
    int fsize = ftell(out_file);
    rewind(out_file);

    symbol *sym = NULL;
    symbol *psym = NULL;
    unsigned char *ch = (unsigned char *) malloc(fsize * sizeof(unsigned char));

    fread(ch, 1, fsize, out_file);
    for (int i = 0; i < fsize; i++)
    {
        psym = sym;
        if (sym == NULL)
        {
            sym = (symbol *) malloc(sizeof(symbol));
            sym->ch = ch[i];
            sym->freq = 1;
            sym->next = NULL;
        }
        else
        {
            while (1)
            {
                if (psym->ch == ch[i])
                {
                    psym->freq++;
                    break;
                }
                if (psym->next == NULL)
                {
                    symbol *new_sym = (symbol *) malloc(sizeof(symbol));
                    new_sym->ch = ch[i];
                    new_sym->freq = 1;
                    new_sym->next = NULL;
                    psym->next = new_sym;
                    break;
                }
                psym = psym->next;
            }
        }
    }
    fclose(out_file);
    free(ch);
    return sym;
}