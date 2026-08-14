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
	
	if (c != index)
		head = NULL;
	return (head);
}

/**
 * delete_dnodeint_at_index - delete node at index
 * @head: list
 * @index: what node
 *
 * Return: 1 on succes, -1 of failure
 */

int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *prev_node;
	dlistint_t *next_node;

	if (*head == NULL)
		return (-1);

	if (index == 0)
	{
		next_node = *head;
		if (next_node->next == NULL)
		{
			free(*head);
			*head = NULL;
		}
		else
		{
			next_node = next_node->next;
			free(next_node->prev);
			next_node->prev = NULL;
			*head = next_node;
		}
	}
	else
	{
		prev_node = get_dnodeint_at_index(*head, index - 1);
		if (prev_node == NULL)
			return (-1);

		next_node = prev_node->next;
		prev_node->next = next_node->next;
		next_node->next->prev = prev_node;
		free(next_node);
	}
	return (1);
}
