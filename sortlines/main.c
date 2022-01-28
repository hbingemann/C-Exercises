#include <stdio.h>
#include <string.h>
#include "rwlines.h"
#include "sortlines.h"

#define MAXLINES 5000

char *lineptr[MAXLINES];

int main()
{
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        quicksort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

