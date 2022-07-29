#include <stdio.h>
#include <string.h>
#include "type.h"
#include "file_lib.h"
#include "math_lib.h"

void help()
{
    printf("\nWelcome!!!\n");
    printf("Enter the file name as the first argument: file.txt\n");
    printf("The program counts each character\n"); 
    printf("and sorts the characters in descending order.\n");
}

int main(int argc, char *argv[])
{ 
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            help();
            return 0;
        }
    }

    symbol *sym = NULL;

    sym = out_file(argv[1]);
    for (symbol *i = sym; i != NULL; i = i->next)
    {
    printf("%c - %f\n", i->ch, i->freq);
    }
    printf ("\n\n");
    
    sym = descen_sort(sym);
    for (symbol *i = sym; i != NULL; i = i->next)
    {
    printf("%c - %f\n", i->ch, i->freq);
    }
    printf("\n\n");
    for (symbol *i = sym; i != NULL;)
    {
        symbol *next = i->next;
        free(i);
        i = next;
    }

    return 0;
}