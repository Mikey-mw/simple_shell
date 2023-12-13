#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @shell_info: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(shell_info_t *shell_info, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		shell_info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		shell_info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		shell_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = j;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @shell_info: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buf
 * @start_position: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */
void check_chain(shell_info_t *shell_info, char *buffer, size_t *position, size_t start_position, size_t length)
{
	size_t j = *position;

	if (shell_info->cmd_buf_type == CMD_AND)
	{
		if (shell_info->status)
		{
			buffer[start_position] = 0;
			j = length;
		}
	}
	if (shell_info->cmd_buf_type == CMD_OR)
	{
		if (!shell_info->status)
		{
			buffer[start_position] = 0;
			j = length;
		}
	}

	*position = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @shell_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(shell_info_t *shell_info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(shell_info->alias, shell_info->argv[0], '=');
		if (!node)
			return (0);
		free(shell_info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		shell_info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @shell_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(shell_info_t *shell_info)
{
	int i = 0;
	list_t *node;

	for (i = 0; shell_info->argv[i]; i++)
	{
		if (shell_info->argv[i][0] != '$' || !shell_info->argv[i][1])
			continue;

		if (!_strcmp(shell_info->argv[i], "$?"))
		{
			replace_string(&(shell_info->argv[i]),
				_strdup(convert_number(shell_info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(shell_info->argv[i], "$$"))
		{
			replace_string(&(shell_info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(shell_info->env, &shell_info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(shell_info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&shell_info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old_str: address of old string
 * @new_str: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
