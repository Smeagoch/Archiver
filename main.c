#include <stdio.h>
#include <string.h>
#include "type.h"
#include "file_lib.h"
#include "math_lib.h"

#define TOO_MUCH_ARGS 1
#define NO_ARGS 2
#define LATE_FLAG 3

void help()
{
    printf("\nWelcome!!!\n");
    printf("Enter the file name as the first argument: file.txt\n");
    printf("The program counts each character\n"); 
    printf("and sorts the characters in descending order.\n");
}

int main(int argc, char *argv[])
{ 
    if (argc == 1)
    {
        printf("Error!!! Not have arguments\n");
        return NO_ARGS;
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            help();
            return 0;
        }
    }
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            printf("Error!!! The late flag\n");
            return LATE_FLAG;
        }
    }
    if (argc > 2)
    {
        printf("Error!!! More argumenst!!!\n");
        return TOO_MUCH_ARGS;
    }

    symbol *sym;
    int size = 0;

    sym = out_file(argv[1], &size);
    for (int i = 0; i < size; i++)
    {
        printf("%c - %f - %s\n", sym[i].ch, sym[i].freq, sym[i].code);
    }
    printf ("\n\n");
    
    descen_sort(sym, size);

    symbol *branch = NULL;
    int nbranch = 0;
    symbol *tree_begin = make_tree(sym, &size, branch, &nbranch);
    coder_tree(tree_begin, size, NULL, 0);

    for (int i = 0; i < size; i++)
    {
        printf("%c - %f - %s\n", sym[i].ch, sym[i].freq, sym[i].code);
    }
    printf("\n\n");

    free(sym);

    return 0;
}