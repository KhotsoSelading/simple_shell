#include "main.h"

/**
 * display_prompt - displays prompt
 */
void display_prompt(void)
{
	write(IN, "$ ", 2);
}

/**
 * display_out - displays prompt
 * @message: message to write
 */
void display_out(char *message)
{
	write(OUT, message, str_len(message));
}

/**
 * display_err - displays prompt
 * @message: message to write
 */
void display_err(char *message)
{
	write(ERR, message, str_len(message));
}

/**
 * ignore_comm - deletes comments from the input
 *
 * @line: input string
 * Return: input without comments
 */
char *ignore_comm(char *line)
{
	int idx = 0, until = 0, jdx = 0;
	char space = ' ', tab = '\t', s_colon = ';';
	char pound = '#';

	while (line[idx])
	{
		jdx = idx - 1;
		if (line[idx] == pound)
		{
			if (idx == 0)
			{
				free(line);
				return (NULL);
			}

			if (line[jdx] == space || line[jdx] == tab
			|| line[jdx] == s_colon)
				until = idx;
		}
		idx++;
	}

	if (until != 0)
	{
		line = _realloc(line, idx, until + 1);
		line[until] = '\0';
	}

	return (line);
}

/**
 * loop_parser - loop of shell
 * @globvar: data relevant (av, line_in, args)
 *
 * Return: no return.
 */
void loop_parser(globals_t *globvar)
{
	int infinite = 1, ret_eof = 0;
	char *line_in = NULL;

	infinite = 1;
	for (; infinite != 0;)
	{
		display_prompt();
		line_in = line_buff(&ret_eof);
		if (ret_eof != -1)
		{
			line_in = ignore_comm(line_in);
			if (line_in == NULL)
				continue;

			if (syn_err_ch(globvar, line_in) == 1)
			{
				globvar->exitstat = DEFERR;
				free(line_in);
				continue;
			}
			line_in = replacement(line_in, globvar);
			infinite = process_cmd(globvar, line_in);
			globvar->linecount += 1;
			free(line_in);
		}
		else
		{
			infinite = 0;
			free(line_in);
		}
	}
	free_my_globals(globvar);
}
