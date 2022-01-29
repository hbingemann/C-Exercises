#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSTACK 100  /* max size of stack */
#define MAXOP 5  /* max length of character */
#define NUMBER '0'  /* some value to represent a number */

int stack[MAXSTACK];
int *cp = stack;

int pop(void);
char getop(char *);
void push(int);

int main(int argc, char *argv[])
{
    int op2;

    while (--argc > 0) {
        switch (getop(*++argv)) {
            case NUMBER:
                push(atoi(*argv));
                break;
            case '+':
                push(pop() + pop());
                break;
            case 'x':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor");
                break;
            default:
                printf("error: unknown command %s\n", *argv);
                break;
        }
    }
    printf("%i\n", *stack);
}

char getop(char *s)
{
    if (isdigit(*s))
        return NUMBER;
    return *s;

}

void push(int n)
{
    *cp++ = n;
}

int pop()
{
    return *--cp;
}
