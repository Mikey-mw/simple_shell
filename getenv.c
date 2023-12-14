#include "shell.h"

/**
 * obtainEnvironment - returns the string array copy of our environ
 * @information: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **obtainEnvironment(info_t *information)
{
	if (!information->environ || information->envChanged)
	{
		information->environ = listToStrings(information->env);
		information->envChanged = 0;
	}

	return (information->environ);
}

/**
 * _removeEnvVar - Remove an environment variable
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @variable: the string env var property
 */
int _removeEnvVar(info_t *information, char *variable)
{
	list_t *node = information->env;
	size_t index = 0;
	char *ptr;

	if (!node || !variable)
		return (0);

	while (node)
	{
		ptr = startsWith(node->str, variable);
		if (ptr && *ptr == '=')
		{
			information->envChanged = deleteNodeAtIndex(&(information->env), index);
			index = 0;
			node = information->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (information->envChanged);
}

/**
 * _setEnvironment - Initialize a new environment variable,
 *             or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setEnvironment(info_t *information, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_copyString(buffer, variable);
	_concatenateStrings(buffer, "=");
	_concatenateStrings(buffer, value);
	node = information->env;
	while (node)
	{
		ptr = startsWith(node->str, variable);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			information->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(information->env), buffer, 0);
	free(buffer);
	information->envChanged = 1;
	return (0);
}

