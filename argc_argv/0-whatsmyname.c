#include <stdio.h>

/**
 * main - prints own name
 * @argc: amount of arguments
 * @argv: extra arguments
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	printf("%s\n", argv[argc - 1]);
	return (0);
}
