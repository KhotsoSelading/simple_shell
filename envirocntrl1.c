#include "main.h"

/**
 * ret_enviro - get an environment variable
 * @nm: name of the environment variable
 * @e_n_v: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *ret_enviro(const char *nm, char **e_n_v)
{
	char *envptr = NULL;
	int i = 0, shift = 0;

	while (e_n_v[i])
	{
		shift = mat_nm(e_n_v[i], nm);
		if (shift)
		{
			envptr = e_n_v[i];
			break;
		}
		i += 1;
	}

	return (envptr + shift);
}

/**
 * mat_nm - compares env variables names
 * with the name passed.
 * @var_name: name of the environment variable
 * @input: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int mat_nm(const char *var_name, const char *input)
{
	int idx = 0, ret = 0;
	char seperator = '=';

	while (var_name[idx] != seperator)
	{
		if (var_name[idx] != input[idx])
		{
			return (0);
		}
		idx += 1;
	}
	ret = idx + 1;
	return (ret);
}

/**
 * env_printer - prints the evironment variables
 *
 * @globvar: data relevant.
 * Return: 1 on success.
 */
int env_printer(globals_t *globvar)
{
	int a = 0, b = 0;
	char *newln = "\n";

	for (; globvar->my_env[a]; a++)
	{

		for (b = 0; globvar->my_env[a][b]; b++)
			;

		display_out(globvar->my_env[a]);
		display_out(newln);
	}
	globvar->exitstat = 0;

	return (1);
}
