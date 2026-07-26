#include <stdio.h>
#include "dog.h"

/**
 * print_dog - prints a struct dog
 * @d: custom dog var name
 *
 */

void print_dog(struct dog *d)
{
	if (d == NULL)
		return;

	if (d->name == NULL)
		printf("Name: (nil)\n");
	else
		printf("Name: %s\n", d->name);

	if (d->name == NULL)
		printf("Name: (nil)\n");
	else
		printf("Name: %f\n", d->age);

	if (d->name == NULL)
		printf("Name: (nil)\n");
	else
		printf("Name: %s\n", d->owner);

}
