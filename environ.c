#include "shell.h"

/**
 * _displayEnvironment - prints the current environment
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _displayEnvironment(info_t *data)
{
    printListStr(data->env);
    return (0);
}

/**
 * _getEnvironmentVariable - gets the value of an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getEnvironmentVariable(info_t *data, const char *name)
{
    list_t *node = data->env;
    char *p;

    while (node)
    {
        p = startsWith(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _initializeEnvironmentVariable - Initialize a new environment variable,
 *                                  or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _initializeEnvironmentVariable(info_t *data)
{
    if (data->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setEnvironmentVariable(data, data->argv[1], data->argv[2]))
        return (0);
    return (1);
}

/**
 * _removeEnvironmentVariable - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _removeEnvironmentVariable(info_t *data)
{
    int i;

    if (data->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= data->argc; i++)
        _unsetEnvironmentVariable(data, data->argv[i]);

    return (0);
}

/**
 * populateEnvironmentList - populates environment linked list
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(info_t *data)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);
    data->env = node;
    return (0);
}

