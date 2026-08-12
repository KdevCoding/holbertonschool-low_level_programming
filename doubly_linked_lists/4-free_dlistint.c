#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * free_dlistint - free linked list
 * @head: list
 *
 *
 *
 */

void free_dlistint(dlistint_t *head)
{
	dlistint_t *next;

	if (head == NULL)
		return;

	while (head->next != NULL)
	{
		next = head->next;
		free(head);
		head = next;
	}
	free(head);
}
