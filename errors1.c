#include "shell.h"

/**
 * _errStringToInt - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _errStringToInt(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printError - prints an error message
 * @info: the parameter & return info struct
 * @errorString: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printError(info_t *info, char *errorString)
{
	_outputString(info->filename);
	_outputString(": ");
	printDecimal(info->lineCount, STDERR_FILENO);
	_outputString(": ");
	_outputString(info->argv[0]);
	_outputString(": ");
	_outputString(errorString);
}

/**
 * printDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimal(int input, int fileDescriptor)
{
	int (*outputCharacter)(char) = _outputCharacter;
	int index, count = 0;
	unsigned int absoluteValue, current;

	if (fileDescriptor == STDERR_FILENO)
		outputCharacter = _outputCharacter;
	if (input < 0)
	{
		absoluteValue = -input;
		outputCharacter('-');
		count++;
	}
	else
		absoluteValue = input;
	current = absoluteValue;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absoluteValue / index)
		{
			outputCharacter('0' + current / index);
			count++;
		}
		current %= index;
	}
	outputCharacter('0' + current);
	count++;

	return (count);
}

/**
 * convertNumber - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convertNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removeComments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void removeComments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

