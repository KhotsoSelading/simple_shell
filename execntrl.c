#include "main.h"

/**
 * scolon_ch - checks ":" if is in the current directory.
 * @pdir: type char pointer char.
 * @idx: type int pointer of index.
 * Return: 1 if the pdir is searchable in the cd, 0 otherwise.
 */
int scolon_ch(char *pdir, int *idx)
{
	char col = ';';

	if (*(pdir + *idx) == col)
		return (1);
	for (; *(pdir + *idx) != col && *(pdir + *idx);)
	{
		*idx += 1;
	}
	if (*(pdir + *idx))
		*idx += 1;
	return (0);
}

/**
 * pathfinder - locates a command
 *
 * @command: command name
 * @e_n_v: environment variable
 * Return: location of the command.
 */
char *pathfinder(char *command, char **e_n_v)
{
	char *pdir = NULL, *ppdir = NULL, *tdir = NULL, *d = NULL, *cl = ":";
	int lengthd = 0, lengthc = 0, idx = 0;
	struct stat st;

	pdir = ret_enviro("PATH", e_n_v);
	if (pdir)
	{
		ppdir = _strdup(pdir);
		lengthc = str_len(command);
		tdir = str_tok(ppdir, cl);
		for (idx = 0; tdir != NULL;)
		{
			if (scolon_ch(pdir, &idx))
				if (stat(command, &st) == 0)
					return (command);
			lengthd = str_len(tdir);
			d = malloc(lengthd + lengthc + 2);
			_strcpy(d, tdir);
			str_cat(d, "/");
			str_cat(d, command);
			str_cat(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(ppdir);
				return (d);
			}
			free(d);
			tdir = str_tok(NULL, cl);
		}
		free(ppdir);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (*command == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * exec_ch - determines if is an executable
 *
 * @globvar: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int exec_ch(globals_t *globvar)
{
	struct stat st;
	int idx = 0;
	char *ln_in = NULL, dot = '.', fs = '/';

	ln_in = globvar->mytok[0];
	for (; *(ln_in + idx); idx++)
	{
		if (*(ln_in + idx) == dot)
		{
			if (ln_in[idx + 1] == dot)
				return (0);
			if (ln_in[idx + 1] == fs)
				continue;
			else
				break;
		}
		else if (*(ln_in + idx) == fs && idx != 0)
		{
			if (ln_in[idx + 1] == dot)
				continue;
			idx += 1;
			break;
		}
		else
			break;
	}
	if (idx == 0)
		return (0);

	if (stat(ln_in + idx, &st) == 0)
	{
		return (idx);
	}
	err_choose(globvar, SYNERR);
	return (-1);
}

/**
 * err_cmd_type - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @globvar: data structure
 * Return: 1 if there is an error, 0 if not
 */
int err_cmd_type(char *dir, globals_t *globvar)
{
	if (dir == NULL)
	{
		err_choose(globvar, SYNERR);
		return (1);
	}
	if (_strcmp(globvar->mytok[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			err_choose(globvar, PERMERR);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(globvar->mytok[0], X_OK) == -1)
		{
			err_choose(globvar, PERMERR);
			return (1);
		}
	}
	return (0);
}

/**
 * handle_ex - executes command lines
 *
 * @globvar: data relevant (args and ln_in)
 * Return: 1 on success.
 */
int handle_ex(globals_t *globvar)
{
	pid_t mypid = 0, wifpid = 0;
	int state = 0, e_x_e = 0;
	char *dir = NULL;
	(void) wifpid;

	e_x_e = exec_ch(globvar);
	if (e_x_e == -1)
		return (1);
	if (e_x_e == 0)
	{
		dir = pathfinder(globvar->mytok[0], globvar->my_env);
		if (err_cmd_type(dir, globvar) == 1)
			return (1);
	}
	mypid = fork();
	if (mypid < 0)
	{
		perror(globvar->argv[0]);
		return (1);
	}
	else if (mypid == 0)
	{
		if (e_x_e == 0)
			dir = pathfinder(globvar->mytok[0], globvar->my_env);
		else
			dir = globvar->mytok[0];
		execve(dir + e_x_e, globvar->mytok, globvar->my_env);
	}
	else
	{
		do {
			wifpid = waitpid(mypid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	globvar->exitstat = state / STTEMAX;
	return (1);
}
