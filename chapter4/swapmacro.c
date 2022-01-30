/*
 * swap-macro.c
 *
 *  Created on: Jan 25, 2022
 *      Author: henri
 */

#include <stdio.h>
#include <stdlib.h>

#define swap(t, x, y) t temp = x; x = y; y = temp;

//int main()
//{
//	int x = 4;
//	int y = 3;
//	swap(int, x, y);
//	printf("x=%i, y=%i", x, y);
//	return EXIT_SUCCESS;
//}
