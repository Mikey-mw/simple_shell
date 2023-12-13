#include "shell.h"

/**
 * _display_history - displays the history list, one command by line,
 *                    preceded with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _display_history(info_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * remove_alias - sets alias to string
 * @data: parameter struct
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *data, char *alias_str)
{
	char *ptr, c;
	int ret;

	ptr = _strchr(alias_str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, alias_str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * add_alias - sets alias to string
 * @data: parameter struct
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int add_alias(info_t *data, char *alias_str)
{
	char *ptr;

	ptr = _strchr(alias_str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (remove_alias(data, alias_str));

	remove_alias(data, alias_str);
	return (add_node_end(&(data->alias), alias_str, 0) == NULL);
}

/**
 * print_alias_string - prints an alias string
 * @alias_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_string(list_t *alias_node)
{
	char *ptr = NULL, *str = NULL;

	if (alias_node)
	{
		ptr = _strchr(alias_node->str, '=');
		for (str = alias_node->str; str <= ptr; str++)
			_putchar(*str);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _manage_alias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _manage_alias(info_t *data)
{
	int i = 0;
	char *ptr = NULL;
	list_t *alias_node = NULL;

	if (data->argc == 1)
	{
		alias_node = data->alias;
		while (alias_node)
		{
			print_alias_string(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		ptr = _strchr(data->argv[i], '=');
		if (ptr)
			add_alias(data, data->argv[i]);
		else
			print_alias_string(node_starts_with(data->alias, data->argv[i], '='));
	}

	return (0);
}

