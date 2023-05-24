
#include "main.h"

/**
 * build_cd_err - function that concatenates the message for cd er
 *
 * @globvar: data relevant (directory)
 * @m: message to print
 * @er: output message
 * @lncount: counter lines
 * Return: er message
 */
char *build_cd_err(globals_t *globvar, char *m, char *er, char *lncount)
{
	char *warning = NULL, *seperator = ": ", dash = '-', nol = '\0';
	char *newln = "\n", *nnol = "\0";

	_strcpy(er, globvar->argv[0]);
	str_cat(er, seperator);
	str_cat(er, lncount);
	str_cat(er, seperator);
	str_cat(er, globvar->mytok[0]);
	str_cat(er, m);
	if (globvar->mytok[1][0] == dash)
	{
		warning = malloc(sizeof(char) * 3);
		*warning = dash;
		*(warning + 1) = globvar->mytok[1][1];
		*(warning + 2) = nol;
		str_cat(er, warning);
		free(warning);
	}
	else
	{
		str_cat(er, globvar->mytok[1]);
	}
	str_cat(er, newln);
	str_cat(er, nnol);
	return (er);
}

/**
 * check_cd_er - er message for cd command in get_cd
 * @globvar: data relevant (directory)
 * Return: er message
 */
char *check_cd_er(globals_t *globvar)
{
	int len = 0, len2 = 0;
	char *er = NULL;
	char *lncount = NULL;
	char *m = NULL, dash = '-';
	char *message1 = ": Illegal option ", *message2 = ": can't cd to ";

	lncount = num_tostr(globvar->linecount);
	if (globvar->mytok[1][0] == dash)
	{
		m = message1;
		len2 = DEFERR;
	}
	else
	{
		m = message2;
		len2 = str_len(globvar->mytok[1]);
	}
	len = str_len(globvar->argv[0]) + str_len(globvar->mytok[0]);
	len = len + str_len(lncount) + str_len(m) + len2 + 5;
	er = malloc(sizeof(char) * (len + 1));
	if (er == 0)
	{
		free(lncount);
		return (NULL);
	}
	er = build_cd_err(globvar, m, er, lncount);
	free(lncount);
	return (er);
}

/**
 * location_err - generic er message for command not found
 * @globvar: data relevant (counter, arguments)
 * Return: er message
 */
char *location_err(globals_t *globvar)
{
	char *er = NULL, *lncount = NULL;
	int len = 0;
	char *nol = "\0", *sep = ": ", *m = ": not found\n";

	lncount = num_tostr(globvar->linecount);
	len = str_len(globvar->argv[0]) + str_len(lncount);
	len = len + str_len(globvar->mytok[0]) + 16;
	er = malloc(sizeof(char) * (len + 1));

	if (er == NULL)
	{
		free(er);
		free(lncount);
		return (NULL);
	}
	_strcpy(er, globvar->argv[0]);

	str_cat(er, sep);
	str_cat(er, lncount);
	str_cat(er, sep);

	str_cat(er, globvar->mytok[0]);
	str_cat(er, m);
	str_cat(er, nol);

	free(lncount);
	return (er);
}

/**
 * gen_ext_err - generic er message for exit in get_exit
 * @globvar: data relevant (counter, arguments)
 *
 * Return: er message
 */
char *gen_ext_err(globals_t *globvar)
{
	int len = 0, mv = 23;
	char *er = NULL, *lncount = NULL;
	char *sep = ": ", *message = ": Illegal number: ";
	char *sep2 = "\n\0";

	lncount = num_tostr(globvar->linecount);
	len = str_len(globvar->argv[0]) + str_len(lncount);

	len = len + str_len(globvar->mytok[0]) + str_len(globvar->mytok[1]) + mv;
	er = malloc(sizeof(char) * (len + 1));

	if (er == NULL)
	{
		free(lncount);
		return (NULL);
	}
	_strcpy(er, globvar->argv[0]);
	str_cat(er, sep);
	str_cat(er, lncount);
	str_cat(er, sep);

	str_cat(er, globvar->mytok[0]);
	str_cat(er, message);
	str_cat(er, globvar->mytok[1]);
	str_cat(er, sep2);

	free(lncount);

	return (er);
}
