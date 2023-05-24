#include "main.h"

/**
 * str_toint - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int str_toint(char *s)
{
	int i, vle = 0, sign = 1, lst = 0;
	char zer = '0', nin = '9', dash = '-', spc = ' ';

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == dash)
			sign = (-1) * sign;

		if (lst > 0 && s[i] == spc)
			break;
		if (vle >= INT_MAX / 10 || (vle == INT_MAX / 10 && s[i] - zer > 7))
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		if (s[i] >= zer && s[i] <= nin)
		{

			vle = vle * 10 + s[i] - zer;
			lst += 1;
		}

	}
	vle = vle * sign;
	return (vle);
}


/**
 * cnt_dgts - Get the len of a number.
 * @num: type int number.
 * Return: len of a number.
 */
int cnt_dgts(int num)
{
	int cnt = 0;

	if (num == 0)
		return (1);

	if (num < 0)
	{
		num = (-1) * num;
		cnt++;
	}

	while (num != 0)
	{
		cnt++;
		num /= 10;
	}
	return (cnt);
}
/**
 * num_tostr - function converts int to string.
 * @num: type int number
 * Return: String.
 */
char *num_tostr(int num)
{
	usnd_int temp;
	char *buf = NULL, zer = '0', dash = '-', nol = '\0';
	int len;

	len = cnt_dgts(num);
	buf = malloc(sizeof(char) * (len + 1));
	if (buf == 0)
		return (NULL);
	buf[len] = nol;
	if (num < 0)
	{
		temp = num * -1;
		buf[0] = dash;
	}
	else
	{
		temp = num;
	}
	len -= 1;
	do {
		buf[len] = (temp % 10) + zer;
		temp = temp / 10;
		len -= 1;
	}
	while (temp > 0)
		;
	return (buf);
}
