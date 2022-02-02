#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void minscanf(char *fmt, ...);

int main()
{
    int d, y;
    char m[100];
    if (scanf("%5s/%d/%d", m, &d, &y) == 3)
        printf("month: %s, day: %d, year: %d\n", m, d, y);
    else
        printf("Invalid input\n");
}


/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, c;
    int ival;
    double dval;
    int fwidth;

    va_start(ap, fmt);
    while ((c = getchar()) != ' ' && c != '\n' && c != '\t' && c != EOF); /*skip whitespace*/

    // compare getchar and format string
    // if they are the same continue
    // if format string has a %
        // get next letter and then check for int / double / string
        // keep getting next char until getchar and format string are equal

    for (p = fmt; *p; p++) {
        fwidth = 0;
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        while ((c = *++p) && c != ' ')
        {
            if (isalpha(c)) {
                switch (c) {
                    case 'd':
                        ival = va_arg(ap, int);
                        fwidth -= printf("%d", ival);
                        break;
                    case 'f':
                        dval = va_arg(ap, double);
                        fwidth -= printf("%f", dval);
                        break;
                    case 's':
                        for (sval = va_arg(ap, char *); *sval; sval++)
                        {
                            putchar(*sval);
                            fwidth--;
                        }
                        break;
                    default:
                        putchar(c);
                        break;
                }
                break;  /* always done at letter */
            } else if (isdigit(c)) {
                fwidth = fwidth * 10 + (c - '0');
            }
        }
        while (fwidth-- > 0)
            putchar(' ');
    }
    va_end(ap);
}