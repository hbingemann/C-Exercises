#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

void minprintf(char *fmt, ...);

int main()
{
    int x = 5;
    char s[] = "bum";
    minprintf("X: %d, %s\n", x, s);
}


/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, c;
    int ival;
    double dval;
    int fwidth = 0;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
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
                        printf("%f", dval);
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
                fwidth = fwidth * 10 + atoi(c);
            }
        }
        while (fwidth-- > 0)
            putchar(' ');
    }
    va_end(ap);
}