#include <stdio.h>
#include <string.h>

#define MAX 1000


void reverse(char *s);

int main()
{
    char s[] = "hello, world";
    printf("%s\n", s);
    reverse(s);
    printf("%s\n", s);
}

void reverse(char *s)
{
    char *t = s;
    char temp;

    while (*(++s + 1) != '\0');  // go to end of s

    for ( ; s - t > 1; s--, t++)
    {
        // swap
        temp = *t;
        *t = *s;
        *s = temp;
    }
}
