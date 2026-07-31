#include <stdio.h>

/**
 * main - prints amount of arguments passed
 * @argc: amount of arguments
 * @argv: extra arguments
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	(void)argv;

	printf("%d\n", (argc - 1));
	return (0);
}
