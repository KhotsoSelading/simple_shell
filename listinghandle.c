#include "main.h"

/**
 * partition_add_end - adds a separator found at the end
 * of a partition.
 * @h: h of the linked list.
 * @part: separator found (; | &).
 * Return: address of the h.
 */
partition *partition_add_end(partition **h, char part)
{
	partition *newnode, *place_holder;

	newnode = malloc(sizeof(partition));
	if (newnode == NULL)
	{
		return (NULL);
	}

	newnode->parts = part;
	newnode->link = NULL;
	place_holder = *h;

	if (place_holder == NULL)
		*h = newnode;
	else
	{
		for (; place_holder->link != NULL;)
			place_holder = place_holder->link;
		place_holder->link = newnode;
	}

	return (*h);
}

/**
 * free_partition - frees a partition
 * @h: h of the linked list.
 * Return: no return.
 */
void free_partition(partition **h)
{
	partition *nxt_ptr;

	if (h == NULL)
		return;

	while (*h)
	{
		nxt_ptr = (*h)->link;
		free(*h);
		*h = nxt_ptr;
	}

	*h = NULL;
}

/**
 * cmdln_add_end - adds a command line at the end
 * of a cmd_t.
 * @h: h of the linked list.
 * @line: command line.
 * Return: address of the h.
 */
cmd_t *cmdln_add_end(cmd_t **h, char *line)
{
	cmd_t *newnode, *temp;

	newnode = malloc(sizeof(cmd_t));
	if (newnode == NULL)
		return (NULL);

	newnode->cmd_args = line;
	newnode->link = NULL;
	temp = *h;

	if (temp == NULL)
	{
		*h = newnode;
	}
	else
	{
		for (; temp->link != NULL;)
			temp = temp->link;
		temp->link = newnode;
	}

	return (*h);
}

/**
 * free_cmd_t - frees a cmd_t
 * @h: h of the linked list.
 * Return: no return.
 */
void free_cmd_t(cmd_t **h)
{
	cmd_t *nxt_ptr;

	if (h == NULL)
		return;

	while (*h)
	{
		nxt_ptr = (*h)->link;
		free(*h);
		*h = nxt_ptr;
	}

	*h = NULL;
}
