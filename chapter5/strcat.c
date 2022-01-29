#include <stdio.h>

#define MAX 1000


void _strcat(char *s, char *t);

int main()
{
    char s[] = "hello";
    char t[] = "world";
    _strcat(s, &t[0]);
    printf("%s\n", s);
}

void _strcat(char *s, char *t)
{
    while (*s != '\0')
        s++;
    while (*t != '\0')
        *s++ = *t++;
}
