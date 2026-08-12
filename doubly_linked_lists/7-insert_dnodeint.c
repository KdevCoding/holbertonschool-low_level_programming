#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * insert_dnodeint_at_index - insert node at index
 * @h: list
 * @idx: where to insert node
 * @n: int val
 * Return: number of nodes
 */

dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *new;
	dlistint_t *head;
	unsigned int c;

	c = 0;
	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
	{
		printf("Error\n");
		return (NULL);
	}

	new->n = n;
	new->next = NULL;

	if (*h == NULL && c == idx)
	{
		*h = new;
	}
	else
	{
		head = *h;

		while (head->next != NULL && c < idx)
		{
			head = head->next;
			c++;
		}
		if (c != idx - 1)
			head = head->prev;

		if (c < idx - 1)
		{
			free(new);
			return (NULL);
		}
		new->prev = head;
		new->next = head->next;
		head->next = new;
	}
	return (new);
}
