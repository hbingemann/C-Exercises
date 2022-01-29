#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char *a, char *b, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int _strcmp(char *s1, char *s2)
{
    return strcmp(s1, s2);
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Usage: ./compare <options> value1 value2");
        return 1;
    }

    int numeric = strcmp(argv[1], "-n") == 0;
    if (numeric && argc != 4 || !numeric && argc != 3)
    {
        printf("Usage: ./compare <options> value1 value2");
        return 1;
    }

    int result = compare(argv[1 + numeric], argv[2 + numeric], (int (*)(void*,void*))(numeric ? numcmp : _strcmp));
    printf("Comparison: %i\n", result);
    
    return 0;
}

int compare(char *a, char *b, int (*comp)(void *, void *))
{
    return (*comp)(a, b);
}

