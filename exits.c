#include "shell.h"

/**
 **_copyString - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@count: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_copyString(char *destination, char *source, int count)
{
	int index, j;
	char *result = destination;

	index = 0;
	while (source[index] != '\0' && index < count - 1)
	{
		destination[index] = source[index];
		index++;
	}
	if (index < count)
	{
		j = index;
		while (j < count)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 **_concatenateStrings - concatenates two strings
 *@first: the first string
 *@second: the second string
 *@count: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_concatenateStrings(char *first, char *second, int count)
{
	int i, j;
	char *result = first;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (second[j] != '\0' && j < count)
	{
		first[i] = second[j];
		i++;
		j++;
	}
	if (j < count)
		first[i] = '\0';
	return (result);
}

/**
 **_findCharacter - locates a character in a string
 *@stringToSearch: the string to be parsed
 *@characterToFind: the character to look for
 *Return: (stringToSearch) a pointer to the memory area stringToSearch
 */
char *_findCharacter(char *stringToSearch, char characterToFind)
{
	do {
		if (*stringToSearch == characterToFind)
			return (stringToSearch);
	} while (*stringToSearch++ != '\0');

	return (NULL);
}

