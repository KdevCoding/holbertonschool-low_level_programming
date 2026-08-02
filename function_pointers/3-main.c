#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "3-calc.h"

/**
 * main - calculator
 * @argc: amount of arguments
 * @argv: arguments
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	int a;
	int b;
	char *op;
	int (*mf)(int, int);

	if (argc == 4)
	{
		a = atoi(argv[1]);
		b = atoi(argv[3]);
		op = argv[2];
		if ((strcmp(op, "/") == 0 || strcmp(op, "%") == 0) && b == 0)
		{
			printf("Error\n");
			return (100);
		}

		mf = get_op_func(op);

		if (mf == NULL)
		{
			printf("Error\n");
			return (99);
		}

		printf("%d\n", mf(a, b));
	}
	else
	{
		printf("Error\n");
		return (98);
	}

	return (0);
}
