#include "main.h"

/**
 * str_cat - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *str_cat(char *dest, const char *src)
{
	int a = 0, b = 0;

	for (a = 0; dest[a]; a++)
		;

	for (b = 0; src[b]; b++)
	{
		dest[a] = src[b];
		a += 1;
	}

	dest[a] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @str1: type str compared
 * @str2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *str1, char *str2)
{
	int a = 0;

	for (a = 0; str1[a] == str2[a] && str1[a]; a++)
		;
	if (str1[a] > str2[a])
		return (1);
	if (str1[a] < str2[a])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	usnd_int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @str: initial segment.
 * @acc: acced bytes.
 * Return: the number of acced bytes.
 */
int _strspn(char *str, char *acc)
{
	int a = 0, b = 0, tracker;

	for (; str[a]; a++)
	{
		tracker = 1;
		for (b = 0; acc[b]; b++)
		{
			if (str[a] == acc[a])
			{
				tracker = 0;
				break;
			}
		}
		if (tracker == 1)
			break;
	}
	return (a);
}
