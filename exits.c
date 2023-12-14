#include "shell.h"

/**
 **_strncpy - copies a string
 *@destination: the destination string to be copied to
 *@src: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *destination, char *src, int num)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		destination[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@destination: the first string
 *@src: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *destination, char *src, int num)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		destination[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		destination[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@ch: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char ch)
{
	do {
		if (*s == ch)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
