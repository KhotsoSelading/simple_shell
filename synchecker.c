#include "main.h"

/**
 * rep_check - counts the repetitions of a char
 *
 * @line_in: input string
 * @idx: index
 * Return: repetitions
 */
int rep_check(char *line_in, int idx)
{
	if (*(line_in - 1) == *line_in)
	{
		return (rep_check(line_in - 1, idx + 1));
	}

	return (idx);
}

/**
 * partition_err - finds syntax errors
 *
 * @line_in: input string
 * @idx: index
 * @end: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int partition_err(char *line_in, int idx, char end)
{
	int len;
	char space = ' ', tab = '\t', bar = '|', s_colon = ';', ampersand = '&';

	len = 0;
	if (line_in[0] == '\0')
		return (0);

	if (line_in[0] == space || line_in[0] == tab)
		return (partition_err(line_in + 1, idx + 1, end));

	if (line_in[0] == s_colon)
		if (end == bar || end == ampersand || end == s_colon)
			return (idx);
	if (line_in[0] == bar)
	{
		if (end == s_colon || end == ampersand)
			return (idx);
		if (end == bar)
		{
			len = rep_check(line_in, 0);
			if (len == 0 || len > 1)
				return (idx);
		}
	}

	if (line_in[0] == ampersand)
	{
		if (end == s_colon || end == bar)
			return (idx);
		if (end == ampersand)
		{
			len = rep_check(line_in, 0);
			if (len == 0 || len > 1)
				return (idx);
		}
	}

	return (partition_err(line_in + 1, idx + 1, *line_in));
}

/**
 * init_ind - finds index of the first char
 *
 * @ln_in: input string
 * @idx: index
 * Return: 1 if there is an error. 0 in other case.
 */
int init_ind(char *ln_in, int *idx)
{
	char bar = '|', spc = ' ', tab = '\t', amp = '&', cln = ';';

	for (*idx = 0; ln_in[*idx]; *idx = *idx + 1)
	{
		if (ln_in[*idx] == spc || ln_in[*idx] == tab)
			continue;

		if (ln_in[*idx] == cln || ln_in[*idx] == bar || ln_in[*idx] == amp)
			return (-1);
		break;
	}

	return (0);
}

/**
 * gen_syn_err - prints when a syntax error is found
 *
 * @globvar: data structure
 * @ln: input string
 * @idx: index of the error
 * @track: to control msg error
 * Return: no return
 */
void gen_syn_err(globals_t *globvar, char *ln, int idx, int track)
{
	char *m1 = NULL, *m2 = NULL, *m3 = NULL, *warning = NULL;
	char *cnt = NULL, *divider = ": ";
	char scol = ';', *sscol = ";;", *_scol = ";", bar = '|', *bbar = "||";
	char *_bar = "|", amp = '&', *aamp = "&&", *_amp = "&";
	int len = 0;

	if (ln[idx] == ';')
	{
		if (track == 0)
			m1 = (ln[idx + 1] == scol ? sscol : _scol);
		else
			m1 = (ln[idx - 1] == scol ? sscol : _scol);
	}
	if (ln[idx] == bar)
		m1 = (ln[idx + 1] == bar ? bbar : _bar);
	if (ln[idx] == amp)
		m1 = (ln[idx + 1] == amp ? aamp : _amp);

	m2 = ": Syntax error: \"", m3 = "\" unexpected\n";
	cnt = num_tostr(globvar->linecount);
	len = str_len(globvar->argv[0]) + str_len(cnt);
	len += str_len(m1) + str_len(m2) + str_len(m3) + 2;
	warning = malloc(sizeof(char) * (len + 1));
	if (warning == 0)
	{
		free(cnt);
		return;
	}
	_strcpy(warning, globvar->argv[0]);
	str_cat(warning, divider);
	str_cat(warning, cnt);
	str_cat(warning, m2);
	str_cat(warning, m1);
	str_cat(warning, m3);
	str_cat(warning, "\0");

	display_err(warning);
	free(warning);
	free(cnt);
}

/**
 * syn_err_ch - intermediate function to
 * find and print a syntax error
 *
 * @globvar: data structure
 * @ln: input string
 * Return: 1 if there is an error. 0 in other case
 */
int syn_err_ch(globals_t *globvar, char *ln)
{
	int start = 0, first = 0, i = 0;

	first = init_ind(ln, &start);
	if (first == -1)
	{
		gen_syn_err(globvar, ln, start, 0);
		return (1);
	}

	i = partition_err(ln + start, 0, ln[start]);
	if (i != 0)
	{
		gen_syn_err(globvar, ln, start + i, 1);
		return (1);
	}

	return (0);
}
