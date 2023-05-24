#include "main.h"

/**
 * _realloc - reallocates memory
 * @place: place to memory to be allocated
 * @o_size: size of memory before allocation
 * @n_size: desired size of memory after allocation
 *
 * Return: address of reallocated memory
 */

void *_realloc(void *place, usnd_int o_size, usnd_int n_size)
{
	void *mem;
	char *copy, *temp;
	usnd_int i;

	if (n_size == o_size)
		return (place);

	if (place == NULL)
	{
		mem = malloc(n_size);
		if (mem == NULL)
			return (NULL);
		return (mem);
	}

	if (n_size == 0 && place != NULL)
	{
		free(place);
		return (NULL);
	}

	copy = place;
	mem = malloc(sizeof(*copy) * n_size);

	if (mem == NULL)
	{
		free(place);
		return (NULL);
	}

	temp = mem;

	for (i = 0; i < o_size && i < n_size; i++)
		temp[i] = *copy++;

	free(place);
	return (mem);
}

/**
 * free_my_globals - frees data structure
 * @globvar: data structure
 * Return: no return
 */
void free_my_globals(globals_t *globvar)
{
	usnd_int idx = 0;

	while (globvar->my_env[idx])
	{
		free(globvar->my_env[idx]);
		idx += 1;
	}
	free(globvar->my_env);
	free(globvar->this_pid);
}

/**
 * dprllc - reallocates a memory block of a double pointer.
 * @place: double pointer to the memory previously allocated.
 * @o_sze: size, in bytes, of the allocated space of place.
 * @nsze: new size, in bytes, of the new memory block.
 *
 * Return: place.
 * if nsze == o_sze, returns place without changes.
 * if malloc fails, returns NULL.
 */
char **dprllc(char **place, usnd_int o_sze, usnd_int nsze)
{
	char **newplace = NULL;
	usnd_int a = 0;

	if (place == NULL)
		return (malloc(sizeof(char *) * nsze));
	if (nsze == o_sze)
		return (place);
	newplace = malloc(sizeof(char *) * nsze);
	if (newplace == NULL)
		return (NULL);
	while (a < o_sze)
	{
		newplace[a] = place[a];
		a += 1;
	}

	free(place);

	return (newplace);
}


/**
 * init_data - Initialize data structure
 *
 * @globvar: data structure
 * @argv: argument vector
 * Return: no return
 */
void init_data(globals_t *globvar, char **argv)
{
	usnd_int a = 0;

	globvar->argv = argv, globvar->linecount = 1;
	globvar->exitstat = 0;
	globvar->mytok = NULL, globvar->line = NULL;

	for (; environ[a]; a++)
		;

	globvar->my_env = malloc(sizeof(char *) * (a + 1));
	a = 0;
	while (environ[a])
	{
		globvar->my_env[a] = _strdup(environ[a]);
		a += 1;
	}

	globvar->this_pid = num_tostr(getpid());

	globvar->my_env[a] = NULL;
}
