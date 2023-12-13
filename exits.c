#include "shell.h"

/**
 **_string_copy - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@max_characters: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_string_copy(char *destination, char *source, int max_characters)
{
	int index_source, index_destination;
	char *start = destination;

	index_source = 0;
	while (source[index_source] != '\0' && index_source < max_characters - 1)
	{
		destination[index_source] = source[index_source];
		index_source++;
	}
	if (index_source < max_characters)
	{
		index_destination = index_source;
		while (index_destination < max_characters)
		{
			destination[index_destination] = '\0';
			index_destination++;
		}
	}
	return (start);
}

/**
 **_string_concatenate - concatenates two strings
 *@first: the first string
 *@second: the second string
 *@max_bytes: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_string_concatenate(char *first, char *second, int max_bytes)
{
	int index_first, index_second;
	char *start = first;

	index_first = 0;
	while (first[index_first] != '\0')
		index_first++;
	index_second = 0;
	while (second[index_second] != '\0' && index_second < max_bytes)
	{
		first[index_first] = second[index_second];
		index_first++;
		index_second++;
	}
	if (index_second < max_bytes)
		first[index_first] = '\0';
	return (start);
}

/**
 **_string_character - locates a character in a string
 *@string: the string to be parsed
 *@character: the character to look for
 *Return: (string) a pointer to the memory area string
 */
char *_string_character(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
