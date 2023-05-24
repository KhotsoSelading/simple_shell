#include "main.h"

/**
 * handle_enviro_err - err message for env in get_env.
 * @sh_data: data relevant (counter, arguments)
 * Return: err message.
 */
char *handle_enviro_err(globals_t *sh_data)
{
	int len = 0;
	char *m = ": Unable to add/remove from environment\n";
	char *err = NULL, *str = NULL, *sep = ": ", *nol = "\0";

	str = num_tostr(sh_data->linecount);
	len = str_len(sh_data->argv[0]) + str_len(str);

	len = len + str_len(sh_data->mytok[0]) + str_len(m) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}

	_strcpy(err, sh_data->argv[0]);
	str_cat(err, sep);
	str_cat(err, str);
	str_cat(err, sep);

	str_cat(err, sh_data->mytok[0]);
	str_cat(err, m);
	str_cat(err, nol);
	free(str);

	return (err);
}

/**
 * err_choose - calls the err according the builtin, syntax or permission
 * @globvar: data structure that contains arguments
 * @vler: err value
 * Return: err
 */
int err_choose(globals_t *globvar, int vler)
{
	char *err = NULL, *ext = "exit", *c_d = "cd";

	if (vler == ENVERR)
		err = handle_enviro_err(globvar);
	else if (vler == PERMERR)
		err = gen_perm_err(globvar);
	else if (vler == SYNERR)
		err = location_err(globvar);
	else if (vler == DEFERR)
	{
		if (_strcmp(ext, globvar->mytok[0]) == 0)
			err = gen_ext_err(globvar);
		else if (_strcmp(c_d, globvar->mytok[0]) == 0)
			err = check_cd_er(globvar);
	}

	if (err)
	{
		display_err(err);
		free(err);
	}

	globvar->exitstat = vler;
	return (vler);
}


/**
 * gen_perm_err - err message for path and failure denied permission.
 * @sh_data: data relevant (counter, arguments).
 *
 * Return: The err string.
 */
char *gen_perm_err(globals_t *sh_data)
{
	int len = 0, mv = 24;
	char *str = NULL, *err = NULL, *sep = ": ", *nol = "\0";
	char *message = ": Permission denied\n";

	str = num_tostr(sh_data->linecount);
	len = str_len(sh_data->argv[0]) + str_len(str);

	len = len + str_len(sh_data->mytok[0]) + mv;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}
	_strcpy(err, sh_data->argv[0]);
	str_cat(err, sep);
	str_cat(err, str);

	str_cat(err, sep);
	str_cat(err, sh_data->mytok[0]);

	str_cat(err, message);
	str_cat(err, nol);
	free(str);
	return (err);
}
