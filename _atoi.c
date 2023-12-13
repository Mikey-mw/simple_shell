#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @ch: the char to check
 * @delim_str: the delimeter string
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
 * _isalpha - checks for alphabetic character
 * @input: The character to input
 * Return: 1 if char_input is alphabetic, 0 otherwise
 */
int _isalpha(int input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
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
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0;  str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
