#include "main.h"

/**
 * line_buff - reads the input string.
 *
 * @ret_eof: return value of getline function
 * Return: input string
 */
char *line_buff(int *ret_eof)
{
	char *ln = NULL;
	size_t place_holder = 0;

	*ret_eof = getline(&ln, &place_holder, stdin);

	return (ln);
}


/**
 * handle_exit - exits the shell
 *
 * @globvar: data relevant (status and args)
 * Return: 0 on success.
 */
int handle_exit(globals_t *globvar)
{
	usnd_int stat = 0;
	int checknum = 0, strln = 0, maxnum = 0, result = 0;

	if (globvar->mytok[1] != NULL)
	{
		stat = str_toint(globvar->mytok[1]);
		checknum = num_detect(globvar->mytok[1]);
		strln = str_len(globvar->mytok[1]);
		maxnum = stat > (usnd_int)INT_MAX;
		if (checknum == 0 || strln > 10 ||
		maxnum)
		{
			err_choose(globvar, DEFERR);
			globvar->exitstat = DEFERR;
			return (1);
		}
		result = (stat % STTEMAX);
		globvar->exitstat = result;
	}
	return (0);
}

/**
 * ret_builts - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*ret_builts(char *cmd))(globals_t *)
{
	int a = 0;
	my_built_ins bui[] = {
		{ "unsetenv", usenv },
		{ "env", env_printer },
		{ "cd", cntrl_cd },
		{ "setenv", senv },
		{ "exit", handle_exit },
		{ NULL, NULL }
	};

	while (bui[a].exec_name)
	{
		if (_strcmp(bui[a].exec_name, cmd) == 0)
			break;

		a += 1;
	}

	return (bui[a].call_func);
}


/**
 * handle_C_sig - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void handle_C_sig(int __attribute__((unused))sig)
{
	char *pmt = "\n$ ";

	display_out(pmt);
	signal(SIGINT, handle_C_sig);
}

/**
 * main - Entry point
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success.
 */
int main(int __attribute__((unused))argc, char **argv)
{
	globals_t globvar;

	signal(SIGINT, handle_C_sig);

	init_data(&globvar, argv);

	loop_parser(&globvar);
	if (globvar.exitstat < 0)
		return (STTEMAX - 1);

	return (globvar.exitstat);
}
