#include <stdio.h>
#include "type.h"

int descen_sort_comparise(const void *sym1, const void *sym2)
{
    float freq1 = ((symbol *) sym1)->freq;
    float freq2 = ((symbol *) sym2)->freq;
    int var = 0;
    if (freq1 < freq2)
        return 1;
    if (freq1 > freq2)
        return -1;
    return 0;
}

void descen_sort(symbol *sym, int size)
{
    qsort(sym, size, sizeof(symbol), &descen_sort_comparise);
}

symbol *make_tree(symbol *sym, int *size, symbol *branch, int *nbranch)
{
    if (branch == NULL)
    {
        branch = (symbol *) malloc((*size - 1) * sizeof(symbol));
        *nbranch = *size - 1;
    }

    symbol *return_sym = (symbol *) malloc(*size * sizeof(symbol));
    for (int i = 0; i < *size; i++)
    {
        return_sym[i] = sym[i];
    }

    symbol *tree_begin;
    int new_size = *size - 1;

    tree_begin = &branch[new_size - 1];

    symbol *min1;
    float min = 1; 
    for (int i = 0; i < *nbranch + 1; i++)
    {
        if (min > sym[*nbranch - i].freq)
        {
            min = sym[*nbranch - i].freq;
            min1 = &sym[*nbranch - i];
        }
    }
    symbol *min2;
    min = 1;
    for (int i = 0; i < *nbranch + 1; i++)
    {
        if ((min > sym[*nbranch - i].freq) && (min1 != &sym[*nbranch - i]))
        {
            min = sym[*nbranch - i].freq;
            min2 = &sym[*nbranch - i];
        }
    }

    branch[new_size - 1].freq = min2->freq + min1->freq;
    if (min1->left == NULL)
    {
        branch[new_size - 1].right = min1;
    }
    else
    {
        branch[new_size - 1].right = min1->left;
    }

    if (min2->left == NULL)
    {
        branch[new_size - 1].left = min2;
    }
    else
    {
        branch[new_size - 1].left = min2->left;
    }
    min2->left = &branch[new_size - 1];
    min2->freq = min2->freq + min1->freq;
    min1->freq = 1;

    if (new_size != 1)
        tree_begin = make_tree(sym, &new_size, branch, nbranch);

    for (int i = 0; i < *size; i++)
    {
        sym[i] = return_sym[i];
    }

    free(return_sym);
    return tree_begin;
}

void coder_tree(symbol *tree_begin, int nsymbol, int *left_right, int passage)
{
    if (passage == 0)
        left_right = (int *) malloc(nsymbol * sizeof(int));
    if ((tree_begin->left != NULL) && (tree_begin->right != NULL))
    {
        symbol *left = tree_begin->left;
        left_right[passage] = 0;
        coder_tree(left, nsymbol, left_right, passage + 1);

        symbol *right = tree_begin->right;
        left_right[passage] = 1;
        coder_tree(right, nsymbol, left_right, passage + 1);
    }
    else
    {
        for (int i = 0; i < passage; i++)
        {
            tree_begin->code[i] = left_right[i] + '0';
        }
        tree_begin->code[passage] = 0;
    }
    if (passage == 0)
    {
        free(left_right);
    }
}