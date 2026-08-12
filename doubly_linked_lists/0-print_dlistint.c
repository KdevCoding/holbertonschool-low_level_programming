#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * print_dlistint - print double linked list
 * @h: list
 *
 *
 * Return: number of nodes
 */

size_t print_dlistint(const dlistint_t *h)
{
	int c;

	c = 0;
	while (h != NULL)
	{

		printf("%u\n", h->n);

		h = h->next;
		c++;
	}
	return (c);
}
