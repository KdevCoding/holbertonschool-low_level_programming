#include <stdarg.h>
#include <stdio.h>
#include "variadic_functions.h"

/**
 * print_str - prints given str
 * @s: sets sep to 1 (to print a seperator)
 * @t: str to print
 *
 */

void print_str(char *t, int *s)
{
	if (t == NULL)
	{
		printf("(nil)");
		*s = 1;
		return;
	}

	printf("%s", t);
	*s = 1;
}

/**
 * print_all - prints given vars
 * @format: format of each var
 *
 *
 */

void print_all(const char *const format, ...)
{
	va_list ap;
	const char *s;
	char *temp;
	int sep;

	va_start(ap, format);
	sep = 0;
	while (format != NULL)
	{
		s = format;
		while (*s && format != NULL)
		{
			if (sep)
				printf(", ");
			sep = 0;
			switch (*s)
			{
			case 'c':
				printf("%c", va_arg(ap, int));
				sep = 1;
				break;
			case 'i':
				printf("%d", va_arg(ap, int));
				sep = 1;
				break;
			case 'f':
				printf("%f", va_arg(ap, double));
				sep = 1;
				break;
			case 's':
				temp = va_arg(ap, char *);
				print_str(temp, &sep);
				break;
			}
			s++;
		}
		va_end(ap);
		printf("\n");
		break;
	}
}
