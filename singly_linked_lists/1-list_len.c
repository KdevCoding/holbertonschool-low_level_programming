#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * list_len - counts number of elements in linked list
 * @h: list
 *
 *
 * Return: number of nodes
 */

size_t list_len(const list_t *h)
{
	int c;

	c = 0;
	while (h != NULL)
	{
		h = h->next;
		c++;
	}
	return (c);
}
