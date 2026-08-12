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
