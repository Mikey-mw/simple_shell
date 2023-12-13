#include "shell.h"

/**
 * obtain_environment - returns the string array copy of our environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **obtain_environment(info_t *info)
{
	if (!info->environment || info->env_updated)
	{
		info->environment = list_to_strings(info->env);
		info->env_updated = 0;
	}

	return (info->environment);
}

/**
 * remove_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @variable: the string env var property
 */
int remove_environment_variable(info_t *info, char *variable)
{
	list_t *current_node = info->env;
	size_t index = 0;
	char *p;

	if (!current_node || !variable)
		return (0);

	while (current_node)
	{
		p = starts_with(current_node->str, variable);
		if (p && *p == '=')
		{
			info->env_updated = delete_node_at_index(&(info->env), index);
			index = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		index++;
	}
	return (info->env_updated);
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *current_node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	current_node = info->env;
	while (current_node)
	{
		p = starts_with(current_node->str, variable);
		if (p && *p == '=')
		{
			free(current_node->str);
			current_node->str = buffer;
			info->env_updated = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_updated = 1;
	return (0);
}
