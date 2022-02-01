#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void minprintf(char *fmt, ...);

int main()
{
    int x = 5555;
    char s[] = "bumsicle";
    minprintf("X :%3d:, :%10s:\n", x, s);
}


/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, c;
    int ival;
    double dval;
    int fwidth;

    va_start(ap, fmt);
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