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
 * delete_dnodeint_at_index - delete node at index
 * @h: list
 * @index: whhat node
 *
 * Return: number of nodes
 */

int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *prev_node;
	dlistint_t *next_node;

	if (index == 0)
	{
		prev_node = head;

		next_node = prev_node->next;
		next_node->prev = NULL;
		free(prev_node);
	}
	else
	{
		prev_node = get_dnodeint_at_index(*head, index - 1);

		next_node = prev_node->next;
		prev_node->next = next_node->next;
		next_node->next->prev = prev_node;
		free(next_node);
	}
	return (1);
}
