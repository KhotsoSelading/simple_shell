#include "main.h"

/**
 * rep_sep - swaps | and & for non-printed chars
 *
 * @ln: ln string
 * @track: type of swap
 * Return: swapped string
 */
char *rep_sep(char *ln, int track)
{
	int idx = 0, sxtn = 16, twlve = 12;
	char bar = '|', amp = '&';

	if (track == 0)
	{
		while (*(ln + idx))
		{
			if (*(ln + idx) == bar)
			{
				if (ln[idx + 1] != bar)
					*(ln + idx) = sxtn;
				else
					idx++;
			}

			if (*(ln + idx) == amp)
			{
				if (ln[idx + 1] != amp)
					*(ln + idx) = twlve;
				else
					idx++;
			}
			idx++;
		}
	}
	else
	{
		idx = 0;
		while (*(ln + idx))
		{
			*(ln + idx) = (*(ln + idx) == sxtn ? bar : *(ln + idx));
			*(ln + idx) = (*(ln + idx) == twlve ? amp : *(ln + idx));
			idx++;
		}
	}
	return (ln);
}

/**
 * place_nds - add separators and command lines in the lists
 *
 * @start_h: head of separator list
 * @last_h: head of command lines list
 * @ln: ln string
 * Return: no return
 */
void place_nds(partition **start_h, cmd_t **last_h, char *ln)
{
	int i = 0;
	char *line = NULL, *delim = ";|&", bar = '|', amp = '&', scl = ';';

	ln = rep_sep(ln, 0);

	while (*(ln + i))
	{
		if (*(ln + i) == scl)
			partition_add_end(start_h, *(ln + i));

		if (*(ln + i) == bar || *(ln + i) == amp)
		{
			partition_add_end(start_h, *(ln + i));
			i++;
		}
		i++;
	}

	line = str_tok(ln, delim);
	do {
		line = rep_sep(line, 1);
		cmdln_add_end(last_h, line);
		line = str_tok(NULL, delim);
	} while (line != NULL);
}

/**
 * jump_to - go to the next command line stored
 *
 * @start_l: separator list
 * @last_l: command line list
 * @globvar: data structure
 * Return: no return
 */
void jump_to(partition **start_l, cmd_t **last_l, globals_t *globvar)
{
	int loop_sep = 1;
	partition *lns;
	cmd_t *lnl;
	char amp = '&', bar = '|', scl = ';';

	lnl = *last_l;
	lns = *start_l;
	for (; lns != NULL && loop_sep;)
	{
		if (globvar->exitstat == 0)
		{
			if (lns->parts == amp || lns->parts == scl)
				loop_sep = 0;
			if (lns->parts == bar)
				lnl = lnl->link, lns = lns->link;
		}
		else
		{
			if (lns->parts == bar || lns->parts == scl)
				loop_sep = 0;
			if (lns->parts == amp)
				lnl = lnl->link, lns = lns->link;
		}
		if (lns != NULL && !loop_sep)
			lns = lns->link;
	}

	*start_l = lns;
	*last_l = lnl;
}

/**
 * process_cmd - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @globvar: data structure
 * @ln: ln string
 * Return: 0 to exit, 1 to continue
 */
int process_cmd(globals_t *globvar, char *ln)
{
	partition *start_h, *start_l;
	cmd_t *last_h, *last_l;
	int loop;

	start_h = NULL;
	last_h = NULL;

	place_nds(&start_h, &last_h, ln);

	start_l = start_h;
	last_l = last_h;

	while (last_l != NULL)
	{
		globvar->line = last_l->cmd_args;
		globvar->mytok = split_to_arr(globvar->line);
		loop = run_exec(globvar);
		free(globvar->mytok);

		if (loop == 0)
			break;

		jump_to(&start_l, &last_l, globvar);

		if (last_l != NULL)
			last_l = last_l->link;
	}

	free_partition(&start_h);
	free_cmd_t(&last_h);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_to_arr - tokizes the ln string
 *
 * @ln: ln string.
 * Return: string splitted.
 */
char **split_to_arr(char *ln)
{
	size_t buf, mybuff = 120, idx = 1;
	char **toks, *tok;

	buf = mybuff + 8;
	toks = malloc(sizeof(char *) * (buf));
	if (toks == NULL)
	{
		display_err("malloc(): failed to allocate memory\n");
		exit(FAILED);
	}

	tok = str_tok(ln, "\v\t\r\n\a ");
	*toks = tok;

	while (tok != NULL)
	{
		if (idx == buf)
		{
			buf += mybuff + 8;
			toks = dprllc(toks, idx, sizeof(char *) * buf);
			if (toks == NULL)
			{
				display_err("malloc(): failed to allocate memory\n");
				exit(FAILED);
			}
		}
		tok = str_tok(NULL, "\v\t\r\n\a ");
		toks[idx] = tok;
		idx++;
	}

	return (toks);
}
