#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * free_list - free linked list
 * @head: list
 *
 *
 *
 */

void free_list(list_t *head)
{
	list_t *next;

	while (head->next != NULL)
	{
		free(head->str);
		next = head->next;
		free(head);
		head = next;
	}

	free(head->str);
	free(head);
}
