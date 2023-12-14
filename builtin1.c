#include "shell.h"

/**
 * _showHistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _showHistory(info_t *data)
{
    printList(data->history);
    return (0);
}

/**
 * _unsetAlias - unsets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unsetAlias(info_t *data, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = deleteNodeAtIndex(&(data->alias),
                            getNodeIndex(data->alias, nodeStartsWith(data->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * _setAlias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _setAlias(info_t *data, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (_unsetAlias(data, str));

    _unsetAlias(data, str);
    return (addNodeEnd(&(data->alias), str, 0) == NULL);
}

/**
 * _printAlias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _printAlias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _manageAlias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _manageAlias(info_t *data)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (data->argc == 1)
    {
        node = data->alias;
        while (node)
        {
            _printAlias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; data->argv[i]; i++)
    {
        p = _strchr(data->argv[i], '=');
        if (p)
            _setAlias(data, data->argv[i]);
        else
            _printAlias(nodeStartsWith(data->alias, data->argv[i], '='));
    }

    return (0);
}

