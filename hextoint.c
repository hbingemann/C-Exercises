/*
 ============================================================================
 Name        : C-Book-Excercises.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int htoi(char s[]);

//int main()
//{
//	char s[] = "0x3fa";
//	printf("hex=%s, dec=%i", s, htoi(s));
//	return EXIT_SUCCESS;
//}

int htoi(char s[])
{
	char c;
	int n = 0;
	for (int i = 2; (c = s[i]) != '\0'; i++)
	{
		if ('0' <= c && c <= '9')
			n = n * 16 + c - '0';
		else if ('a' <= c && c <= 'f')
			n = n * 16 + c - 'a' + 10;
		else if ('A' <= c && c <= 'F')
			n = n * 16 + c - 'A' + 10;
	}
	return n;
}
