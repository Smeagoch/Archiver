#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
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

void in_file(symbol *sym, int size, char *file_name)
{
    FILE *out_file = fopen(file_name, "rb");
    fseek(out_file, 0, SEEK_END);
    int fsize = ftell(out_file);
    rewind(out_file);

    unsigned char *ch = (unsigned char*) malloc(fsize * sizeof(unsigned char));
    fread(ch, 1, fsize, out_file);

    fclose(out_file);

    char *new_file_name = (char *) malloc(sizeof(char));
    for(int i = 0; i < strlen(file_name); i++)
    {
        if (i != 0)
            new_file_name = (char *) realloc(new_file_name, (i + 1) * sizeof(char));
        if (file_name[i] != '.')
            new_file_name[i] = file_name[i];
        else 
        {
            new_file_name[i] = '.';
            new_file_name[i + 1] = 0;
            break;
        }
    }
    char format[] = "ne_hui_Egora";
    new_file_name = (char *) realloc(new_file_name, (strlen(new_file_name) + strlen(format) + 1) * sizeof(char));
    strcat(new_file_name, format);

    FILE *in_file = fopen(new_file_name, "wb");

    char buffer_code[255];
    int ch_to_wr = 0;
    int count_to_wr = 0;
    for(int i = 0; i < fsize; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(ch[i] == sym[j].ch)
            {
                int count = 0;
                while(1)
                {
                    if (sym[j].code[count] - '0' != 0)
                    {
                        ch_to_wr = ch_to_wr + (1 << (7 - count));
                    }
                    if (count_to_wr % 8 != 7)
                    {
                        count_to_wr = count_to_wr + 1;
                    }
                    else
                    {
                        unsigned char wr_ch = ch_to_wr;
                        printf("%c - %d\n", wr_ch, wr_ch);
                        fwrite(&wr_ch, 1, 1, in_file);
                        ch_to_wr = 0;
                        count_to_wr = 0;
                    }
                    count = count + 1;
                    if (count == strlen(sym[j].code))
                    {
                        break;
                    }
                }
                break;
            }
        }
    }
    if (count_to_wr != 1)
    {
        unsigned char wr_ch = ch_to_wr;
        printf("%c - %d\n", wr_ch, wr_ch);
        fwrite(&wr_ch, 1, 1, in_file);
    }
    free(ch);
    free(new_file_name);
    fclose(in_file);
}