#include <stdio.h>
#include <stdlib.h>
#include "dog.h"

/**
 * _strcpy - copies string from src to dest (pointers)
 * @src: pointer to read string
 * @dest: pointer to  destnination for string
 *
 * Return: output dest pointer
 */

char *_strcpy(char *dest, char *src)
{
	int l;

	l = 0;
	while (src[l] != '\0')
	{
		dest[l] = src[l];
		l++;
	}
	dest[l] = src[l];

	return (dest);
}

/**
 * _strlen - counts length of string
 * @s: var to count length
 *
 * Return: returns string length
 */

int _strlen(char *s)
{
	int l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return (l);
}

/**
 * new_dog - create a new struct dog with duplicated strings
 * @name: name of dog
 * @age: age of dog
 * @owner: owner of dog
 *
 * Return: pointer to newly created struct dog, or NULL on failure
 */

dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *d;

	d = malloc(sizeof(dog_t));
	if (d == NULL)
		return (NULL);

	d->name = malloc(_strlen(name) + 1);
	if (d->name == NULL)
	{
		free(d);
		return (NULL);
	}
	_strcpy(d->name, name);

	d->owner = malloc(_strlen(owner) + 1);
	if (d->owner == NULL)
	{
		free(d->name);
		free(d);
		return (NULL);
	}
	_strcpy(d->owner, owner);

	d->age = age;

	return (d);
}
