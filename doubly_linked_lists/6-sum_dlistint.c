#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * sum_dlistint - print double linked list
 * @head: list
 *
 *
 * Return: number of nodes
 */

int sum_dlistint(dlistint_t *head)
{
	int sum;

	sum = 0;
	while (head != NULL)
	{
		sum += head->n;
		head = head->next;

	}
	return (sum);
}
