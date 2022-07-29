#include <stdio.h>
#include "type.h"

void descen_sort(symbol **sym)
{
    symbol *iback = *sym;
    for (symbol *i = *sym; i->next != 0; i = i->next)
    {
        symbol *jback = i;
        for (symbol *j = i->next; j != NULL; j = j->next)
        {
            if (i->freq < j->freq)
            {

                symbol *k = i->next; 
                iback->next = j;
                jback->next = i;
                i->next = j->next;
                j->next = k;
                if (iback == i)
                {
                    *sym = j;
                    iback = *sym;
                }
                k = i;
                i = j;
                j = k;
            }

            jback = j;
        }
        iback = i;
    }
}