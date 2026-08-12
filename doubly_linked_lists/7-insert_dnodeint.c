#include <stdlib.h>
#include <stdio.h>
#include "lists.h"



/**
 * get_dnodeint_at_index - print double linked list
 * @head: list
 * @index: what node to return
 *
 * Return: number of nodes
 */

dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
	unsigned int c;

	c = 0;
	while (head != NULL && c != index)
	{

		head = head->next;
		c++;
	}
	return (head);
}

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
	dlistint_t *prev_node;
	dlistint_t *next_node;

	if (idx == 0)
		return (add_dnodeint(h, n));

	prev_node = get_dnodeint_at_index(*h, idx - 1);
	if (prev_node == NULL)
		return (NULL);

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);
	new->n = n;

	next_node = prev_node->next;
	new->prev = prev_node;
	new->next = next_node;
	prev_node->next = new;
	if (next_node != NULL)
		next_node->prev = new;

	return (new);
}
