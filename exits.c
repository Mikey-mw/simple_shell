#include "shell.h"

/**
 * _copyStringLimited - copies a string up to a specified limit
 * @destination: the destination string to be copied to
 * @source: the source string
 * @limit: the maximum number of characters to be copied
 * Return: the copied string
 */
char *_copyStringLimited(char *destination, char *source, int limit)
{
	int indexDest, indexSrc;
	char *result = destination;

	indexDest = 0;
	while (source[indexSrc] != '\0' && indexSrc < limit - 1)
	{
		destination[indexDest] = source[indexSrc];
		indexDest++;
		indexSrc++;
	}
	if (indexSrc < limit)
	{
		int newIndex = indexSrc;
		while (newIndex < limit)
		{
			destination[newIndex] = '\0';
			newIndex++;
		}
	}
	return result;
}

/**
 * _concatenateStringsLimited - concatenates two strings up to a specified limit
 * @destination: the first string
 * @source: the second string
 * @limit: the maximum number of bytes to be used
 * Return: the concatenated string
 */
char *_concatenateStringsLimited(char *destination, char *source, int limit)
{
	int indexDest, indexSrc;
	char *result = destination;

	indexDest = 0;
	while (destination[indexDest] != '\0')
		indexDest++;
	indexSrc = 0;
	while (source[indexSrc] != '\0' && indexSrc < limit)
	{
		destination[indexDest] = source[indexSrc];
		indexDest++;
		indexSrc++;
	}
	if (indexSrc < limit)
		destination[indexDest] = '\0';
	return result;
}

/**
 * _findCharacter - locates a character in a string
 * @stringToSearch: the string to be parsed
 * @characterToFind: the character to look for
 * Return: (stringToSearch) a pointer to the memory area stringToSearch
 */
char *_findCharacter(char *stringToSearch, char characterToFind)
{
	do {
		if (*stringToSearch == characterToFind)
			return stringToSearch;
	} while (*stringToSearch++ != '\0');

	return NULL;
}

