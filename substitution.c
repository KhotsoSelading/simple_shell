#include "main.h"

/**
 * is_envar - checks if the typed variable is an env variable
 *
 * @h: h of linked list
 * @in: ln_in string
 * @content: content structure
 * Return: no return
 */
void is_envar(variable_t **h, char *in, globals_t *content)
{
	int r = 0, chr = 0, jdx = 1, num = 0;
	char **temp_env;
	char spc = ' ', tab = '\t', scl = ';', nwln = '\n';

	temp_env = content->my_env;
	while (temp_env[r])
	{
		jdx = 1, chr = 0;
		while (temp_env[r][chr])
		{
			if (temp_env[r][chr] == '=')
			{
				num = str_len(temp_env[r] + chr + 1);
				varadd_node(h, jdx, temp_env[r] + chr + 1, num);
				return;
			}

			if (*(in + jdx) == temp_env[r][chr])
				jdx++;
			else
				break;
			chr++;
		}
		r++;
	}
	jdx = 0;
	for (; *(in + jdx); jdx++)
	{
		if (*(in + jdx) == spc || *(in + jdx) == tab ||
		*(in + jdx) == scl || *(in + jdx) == nwln)
			break;
	}

	varadd_node(h, jdx, NULL, 0);
}

/**
 * varbl_ch - check if $$ or $?
 *
 * @h: h of the linked list
 * @in: string ln_in
 * @st: st of Shell
 * @content: content structure
 * Return: no return
 */
int varbl_ch(variable_t **h, char *in, char *st, globals_t *content)
{
	int idx = 0, listat, listpid;
	char tab = '\t', nwln = '\n', nol = '\0', scl = ';', spc = ' ';
	char prmpt = '$', quest = '?';

	listpid = str_len(content->this_pid);
	listat = str_len(st);

	for (idx = 0; in[idx]; idx++)
	{
		if (in[idx] == prmpt)
		{
			if (in[idx + 1] == quest)
				varadd_node(h, 2, st, listat), idx++;
			else if (in[idx + 1] == prmpt)
				varadd_node(h, 2, content->this_pid, listpid), idx++;
			else if (in[idx + 1] == nwln || in[idx + 1] == nol ||
			in[idx + 1] == spc || in[idx + 1] == tab || in[idx + 1] == scl)
				varadd_node(h, 0, NULL, 0);
			else
				is_envar(h, in + idx, content);
		}
	}

	return (idx);
}

/**
 * convert_var - replaces string into variables
 *
 * @h: h of the linked list
 * @ln_in: ln_in string
 * @nln_in: new ln_in string (replaced)
 * @len: new length
 * Return: replaced string
 */
char *convert_var(variable_t **h, char *ln_in, char *nln_in, int len)
{
	variable_t *i;
	int a = 0, b = 0, c = 0;
	char dollar = '$';

	i = *h;
	for (b = a = 0; a < len; a++)
	{
		if (*(ln_in + b) == dollar)
		{
			if (!(i->len1) && !(i->len2))
			{
				nln_in[a] = *(ln_in + b);
				b += 1;
			}
			else if (i->len1 && !(i->len2))
			{
				for (c = 0; c < i->len1; c++)
					b += 1;
				a -= 1;
			}
			else
			{
				c = 0;
				for (; c < i->len2; c++)
				{
					nln_in[a] = i->myvalue[c];
					a++;
				}
				b += (i->len1);
				a -= 1;
			}
			i = i->link;
		}
		else
		{
			nln_in[a] = *(ln_in + b);
			b += 1;
		}
	}
	return (nln_in);
}

/**
 * replacement - calls functions to replace string into vars
 *
 * @ln_in: ln_in string
 * @globvar: content structure
 * Return: replaced string
 */
char *replacement(char *ln_in, globals_t *globvar)
{
	variable_t *h, *i;
	char *st = NULL, *nln_in = NULL;
	int old_l, len;

	st = num_tostr(globvar->exitstat);
	h = NULL;

	old_l = varbl_ch(&h, ln_in, st, globvar);

	if (h == NULL)
	{
		free(st);
		return (ln_in);
	}
	i = h;
	len = 0;

	for (; i != NULL;)
	{
		len += (i->len2 - i->len1);
		i = i->link;
	}
	len += old_l;
	nln_in = malloc(sizeof(char) * (len + 1));
	nln_in[len] = '\0';

	nln_in = convert_var(&h, ln_in, nln_in, len);
	free(ln_in);
	free(st);
	free_variables(&h);

	return (nln_in);
}
