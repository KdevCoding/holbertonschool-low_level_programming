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
	while (head->next != NULL)
	{
		free(head->str);
		head = head->next;
	}

	free(head->str);
	free(head);
}
