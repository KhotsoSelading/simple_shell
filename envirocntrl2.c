#include "main.h"

/**
 * alenv_cp - copies info to create
 * a new env or alias
 * @nm: name (env or alias)
 * @vle: value (env or alias)
 *
 * Return: new env or alias.
 */
char *alenv_cp(char *nm, char *vle)
{
	char *cp = NULL, *equals = "=", *nol = "\0";
	int lnme = 0, lvl = 0, length = 0;

	lvl = str_len(vle);
	lnme = str_len(nm);
	length = lnme + lvl + 2;

	cp = malloc(sizeof(char) * (length));

	_strcpy(cp, nm);
	str_cat(cp, equals);

	str_cat(cp, vle);

	str_cat(cp, nol);

	return (cp);
}

/**
 * assisst_senv - sets an environment variable
 *
 * @nm: name of the environment variable
 * @vle: value of the environment variable
 * @globvar: data structure (environ)
 * Return: no return
 */
void assisst_senv(char *nm, char *vle, globals_t *globvar)
{
	int a = 0, ret = 10;
	char *ravarg = NULL, *nm_arg = NULL;

	while (globvar->my_env[a])
	{
		ravarg = _strdup(globvar->my_env[a]);
		nm_arg = str_tok(ravarg, "=");
		ret = _strcmp(nm_arg, nm);
		if (ret == 0)
		{
			free(globvar->my_env[a]);
			globvar->my_env[a] = alenv_cp(nm_arg, vle);
			free(ravarg);
			return;
		}
		free(ravarg);
		a += 1;
	}
	globvar->my_env = dprllc(globvar->my_env, a, sizeof(char *) * (a + 2));

	globvar->my_env[a] = alenv_cp(nm, vle);

	globvar->my_env[a + 1] = NULL;
}

/**
 * senv - compares env variables names
 * with the name passed.
 * @globvar: glob var
 *
 * Return: 1 on success.
 */
int senv(globals_t *globvar)
{

	if (globvar->mytok[1] == NULL ||
	globvar->mytok[2] == NULL)
	{
		err_choose(globvar, ENVERR);
		return (1);
	}

	assisst_senv(globvar->mytok[1], globvar->mytok[2], globvar);

	return (1);
}

/**
 * usenv - deletes a environment variable
 *
 * @globvar: data relevant (env name)
 *
 * Return: 1 on success.
 */
int usenv(globals_t *globvar)
{
	char **env_alter = NULL, *ravarg = NULL, *nm_arg = NULL;
	int a = 0, b = 0, c = -1;

	if (globvar->mytok[1] == NULL)
	{
		err_choose(globvar, ENVERR);
		return (1);
	}
	while (globvar->my_env[a])
	{
		ravarg = _strdup(globvar->my_env[a]);
		nm_arg = str_tok(ravarg, "=");
		if (_strcmp(nm_arg, globvar->mytok[1]) == 0)
		{
			c = a;
		}
		free(ravarg);
		a += 1;
	}
	if (c == -1)
	{
		err_choose(globvar, ENVERR);
		return (1);
	}
	env_alter = malloc(sizeof(char *) * (a));
	for (a = b = 0; globvar->my_env[a]; a++)
	{
		if (a != c)
		{
			env_alter[b] = globvar->my_env[a];
			b += 1;
		}
	}
	env_alter[b] = NULL;
	free(globvar->my_env[c]);
	free(globvar->my_env);
	globvar->my_env = env_alter;
	return (1);
}
