#include "main.h"

/**
 * _strdup - creates a copy of string allocated in heap
 * @str: string to be allocated
 *
 * Return: address of newly allocated string
 */

char *_strdup(const char *str)
{
	int i = 0;
	int len = 0;
	char *cp;

	len = str_len(str);
	cp = malloc(sizeof(char) * (len + 1));

	if (cp == NULL)
		return (NULL);
	for (i = 0; i <= len; i++)
		cp[i] = str[i];

	return (cp);
}

/**
 * str_len - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int str_len(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * letter_ch - compare chars of strings
 * @s: input string.
 * @part: partiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int letter_ch(char s[], const char *part)
{
	usnd_int a = 0, b = 0, c = 0;

	while (s[a])
	{
		b = 0;
		while (part[b])
		{
			if (s[a] == part[b])
			{
				c++;
				break;
			}
			b++;
		}
		a++;
	}
	if (a == c)
		return (1);
	return (0);
}

/**
 * str_tok - splits a string by some partiter.
 * @str: input string.
 * @part: partiter.
 *
 * Return: string splited.
 */
char *str_tok(char str[], const char *part)
{
	static char *splt, *last;
	char *beginning = NULL, nol = '\0';
	usnd_int idx = 0, track = 0;

	if (str != NULL)
	{
		if (letter_ch(str, part))
			return (NULL);
		splt = str;
		idx = str_len(str);
		last = &str[idx];
	}
	beginning = splt;
	if (beginning == last)
		return (NULL);

	for (; *splt; splt++)
	{
		if (splt != beginning)
			if (*splt && *(splt - 1) == '\0')
				break;
		for (idx = 0; *(part + idx); idx++)
		{
			if (*splt == *(part + idx))
			{
				*splt = nol;
				if (splt == beginning)
					beginning += 1;
				break;
			}
		}
		if (track == 0 && *splt)
			track = 1;
	}
	if (track == 0)
		return (NULL);
	return (beginning);
}

/**
 * num_detect - defines if string passed is a number
 *
 * @str: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int num_detect(const char *str)
{
	usnd_int idx = 0;
	char zero = '0', nine = '9';

	while (str[idx])
	{
		if (str[idx] < zero || str[idx] > nine)
			return (0);
		idx++;
	}
	return (1);
}
