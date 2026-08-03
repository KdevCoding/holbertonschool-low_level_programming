#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * main - print single linked list
 * @h: list
 *
 *
 * Return: number of nodes
 */

size_t print_list(const list_t *h)
{
	int c;

	c = 0;
	while (h != NULL)
	{
		if (h->str == NULL)
		{
			printf("[%u] (nul)\n", h->len);
		}
		else
		{
			printf("[%u] %s\n", h->len, h->str);
		}
		h = h->next;
		c++;
	}
	return (c);
}