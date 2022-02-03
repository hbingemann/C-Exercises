#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 100

char charbuf[BUFSIZE];
int cp = -1;

int minscanf(char *fmt, ...);
char getch(void);
void ungetch(char);


int main()
{
    int month, day, year;
    if (minscanf("%d/%d/%d", &month, &day, &year) == 3)
        printf("month: %d, day: %d, year: %d\n", month, day, year);
    else
        printf("Invalid input\n");
}


/* minscanf: minimal scanf with variable argument list */
int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, c;
    int ival = 0;
    double dval = 0;
    int args_eval = 0;

    while ((c = getch()) == ' ' || c == '\n' || c == '\t')  /*skip whitespace*/
        if (c == EOF)
            return args_eval;

    va_start(ap, fmt);
    for (p = fmt; *p && c && c != EOF; p++, c = getch())
    {
        if (*p != '%') {
            if (*p == c)
                continue;
            else
                return args_eval;
        } else {
            switch (*++p) {
                case 'd':
                    while (isdigit(c))
                    {
                        ival = ival * 10 + (c - '0');
                        c = getch();
                    }
                    ungetch(c);

                    *(va_arg(ap, int *)) = ival;
                    ival = 0;
                    args_eval++;
                    break;
                default:
                    return args_eval;  /* we only expect a 'd' after '%' */
            }
        }
    }

    return args_eval;


    //     while ((c = *++p) && c != ' ')
    //     {
    //         if (isalpha(c)) {
    //             switch (c) {
    //                 case 'd':
    //                     ival = va_arg(ap, int);
    //                     fwidth -= printf("%d", ival);
    //                     break;
    //                 case 'f':
    //                     dval = va_arg(ap, double);
    //                     fwidth -= printf("%f", dval);
    //                     break;
    //                 case 's':
    //                     for (sval = va_arg(ap, char *); *sval; sval++)
    //                     {
    //                         putchar(*sval);
    //                         fwidth--;
    //                     }
    //                     break;
    //                 default:
    //                     putchar(c);
    //                     break;
    //             }
    //             break;  /* always done at letter */
    //         } else if (isdigit(c)) {
    //             fwidth = fwidth * 10 + (c - '0');
    //         }
    //     }
    //     while (fwidth-- > 0)
    //         putchar(' ');
    // }
    va_end(ap);
}

char getch(void)
{
    return cp < 0 ? getchar() : charbuf[cp--];
}

void ungetch(char c)
{
    if (cp >= BUFSIZE)
        printf("ungetch: too many characters");
    else
        charbuf[++cp] = c;
}
