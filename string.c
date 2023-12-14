#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @sh: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *sh)
{
	int i = 0;

	if (!sh)
		return (0);

	while (*sh++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: neg if str1 < str2, pos if str1 > str2, zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @ndl: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @destination: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *destination, char *src)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*src)
		*destination++ = *src++;
	*destination = *src;
	return (ret);
}
