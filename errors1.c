#include "shell.h"

/**
 * _error_string_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _error_string_to_int(char *str)
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
 * print_error_message - prints an error message
 * @info_data: the parameter & return info struct
 * @error_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error_message(info_t *info_data, char *error_str)
{
	_write_stderr(info_data->fname);
	_write_stderr(": ");
	print_decimal(info_data->line_count, STDERR_FILENO);
	_write_stderr(": ");
	_write_stderr(info_data->argv[0]);
	_write_stderr(": ");
	_write_stderr(error_str);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @number: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int number, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (number < 0)
	{
		absolute_value = -number;
		__putchar('-');
		count++;
	}
	else
		absolute_value = number;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
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
 * convert_number_to_string - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number_to_string(long int num, int base, int flags)
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
		*--ptr = char_array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @input_string: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *input_string)
{
	int i;

	for (i = 0; input_string[i] != '\0'; i++)
		if (input_string[i] == '#' && (!i || input_string[i - 1] == ' '))
		{
			input_string[i] = '\0';
			break;
		}
}
