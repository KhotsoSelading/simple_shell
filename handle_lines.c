#include "main.h"

/**
 * varadd_node - adds a variable at the end
 * of a variable_t list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
variable_t *varadd_node(variable_t **head, int lvar, char *val, int lval)
{
	variable_t *new, *temp;

	new = malloc(sizeof(variable_t));
	if (new == NULL)
		return (NULL);

	new->len1 = lvar;
	new->myvalue = val;
	new->len2 = lval;

	new->link = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = new;
	}

	return (*head);
}

/**
 * reverse_str - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void reverse_str(char *s)
{
	int counter = 0;
	char *len;
	char place_holder = 'x';
	int i = 0;

	/*find length of string*/
	len = s;
	while (*len != '\0')
	{
		counter++;
		len += 1;
	}

	for (i = counter - 1; i >= counter / 2; i--)
	{
		place_holder = *(s + i);
		*(s + i) = *(s + counter - i - 1);
		*(s + counter - i - 1) = place_holder;
	}
}

/**
 * run_exec - finds builtins and commands
 *
 * @globvar: data relevant (args)
 * Return: 1 on success.
 */
int run_exec(globals_t *globvar)
{
	int ret = 0, bret = 0;
	int (*my_b)(globals_t *globvar);

	if (globvar->mytok[0] == NULL)
	{
		return (1);
	}
	my_b = ret_builts(globvar->mytok[0]);

	if (my_b != NULL)
	{
		bret = my_b(globvar);
		return (bret);
	}
	ret = handle_ex(globvar);
	return (ret);
}

/**
 * free_variables - frees a variable_t list
 * @h: head of the linked list.
 * Return: no return.
 */
void free_variables(variable_t **h)
{
	variable_t *nxt_ptr;

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

