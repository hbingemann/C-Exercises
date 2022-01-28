#include <ctype.h>
#include <stdio.h>

#define true 1
#define false 0

int getint(int *pn);
int getfloat(float *pn);

int main()
{
    float result;
    getfloat(&result);

    printf("%.2f\n", result);
}

int getfloat(float *pn)
{
    printf("float: ");
    int c, sign, indec;
    float decdiv;

    while (isspace(c = getchar()));

    sign = (c == '-') ? -1 : 1;

    for (*pn = 0; isdigit(c) || c == '.'; c = getchar())
    {
        if (c == '.')
        {
            indec = true;
            decdiv = 10;
            continue;
        }
        if (indec)
        {
            *pn += (c - '0') / decdiv;
            decdiv *= 10;
        }
        else
        {
            *pn = *pn * 10 + (c - '0');
        }
    }
    return c;
}

int getint(int *pn)
{
    printf("Int: ");
    int c, sign;

    while (isspace(c = getchar()));  // skip spaces

    sign = (c == '-') ? -1 : 1;

    for (*pn = 0; isdigit(c); c = getchar())
        *pn = *pn * 10 + (c - '0');

    *pn *= sign;

    return c;
}

