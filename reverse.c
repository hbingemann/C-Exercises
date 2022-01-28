#include <stdio.h>
#include <string.h>

#define MAX 1000


void reverse(char *s);

int main()
{
    char s[] = "hello, world";
    reverse(s);
    printf("%s\n", s);
}

void reverse(char *s)
{
    char t[MAX];
    strcpy(t, s);

    while (++*t != '\0');

    for (int i = 0; *s != '\0'; s++, i++)
        *s = ;

}
