#include "shell.h"

/**
 * _convertStringToInteger - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _convertStringToInteger(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
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
 * displayError - prints an error message
 * @information: the parameter & return information struct
 * @errorString: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void displayError(info_t *information, char *errorString)
{
	_displayString(information->filename);
	_displayString(": ");
	_displayStringToFD(convertToString(information->lineCount), STDERR_FILENO);
	_displayString(": ");
	_displayString(information->arguments[0]);
	_displayString(": ");
	_displayString(errorString);
}

/**
 * displayInteger - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fileDescriptor: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int displayInteger(int input, int fileDescriptor)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absoluteValue, current;

	if (fileDescriptor == STDERR_FILENO)
		__putchar = _displayCharacter;
	if (input < 0)
	{
		absoluteValue = -input;
		__putchar('-');
		count++;
	}
	else
		absoluteValue = input;
	current = absoluteValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absoluteValue / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertNumberToString - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convertNumberToString(long int num, int base, int flags)
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
 * eliminateComments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void eliminateComments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

