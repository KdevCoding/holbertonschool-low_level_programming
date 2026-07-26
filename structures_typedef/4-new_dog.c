#include <stdio.h>
#include "dog.h"

/**
 * new_dog - create a new struct dog
 * @name: name of dog
 * @age: age of dog
 * @owner: owner of dog
 *
 * Return: returns newly made struct dog
 */

dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t dog;
	struct dog *d;

	d = &dog;

	d->name = name;
	d->age = age;
	d->owner = owner;

	if (d == NULL)
		return (NULL);

	return (d);
}
