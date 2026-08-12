#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * dlistint_len - print double linked list
 * @h: list
 *
 *
 * Return: number of nodes
 */

size_t dlistint_len(const dlistint_t *h)
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
