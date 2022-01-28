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
    char ch[MAX];
    strcpy(ch, s);
    char *t = ch;

    while (*(++s + 1) != '\0');  // go to end of s

    for ( ; *t != '\0'; s--, t++)
        *s = *t;
}
