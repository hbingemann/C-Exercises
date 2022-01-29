#include <string.h>
#include <stdio.h>

#define MAXLEN 1000  /* maximum length of any input line */
#define ALLOCSIZE 500000

char allocbuf[ALLOCSIZE];
char *cp = allocbuf;

int _getline(char *s, int lim);
char *alloc(int);

/* read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /*delete newline*/
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
    {
        printf("%s\n", *lineptr++);
    }
}

/* read line into s, return length */
int _getline(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* allocate enough memory for n chars */
char *alloc(int n)
{
    if (cp + n < allocbuf + ALLOCSIZE)
    {
        cp += n;
        return cp - n;
    } else
        return NULL;
}
