#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @data: struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimiter
 * @ch: the char to check
 * @delim_str: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char ch, char *delim_str)
{
	while (*delim_str)
		if (*delim_str++ == ch)
			return (1);
	return (0);
}

/**
 * _is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, result;
	unsigned int output = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			output *= 10;
			output += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -output;
	else
		result = output;

	return (result);
}
