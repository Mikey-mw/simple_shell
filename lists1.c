#include "shell.h"

/**
 * list_len - determines length of linked list
 * @head_ptr: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *head_ptr)
{
	size_t count = 0;

	while (head_ptr)
	{
		head_ptr = head_ptr->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @list_head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *list_head)
{
	list_t *current_node = list_head;
	size_t list_size = list_len(list_head), index;
	char **str_array;
	char *str;

	if (!list_head || !list_size)
		return (NULL);
	str_array = malloc(sizeof(char *) * (list_size + 1));
	if (!str_array)
		return (NULL);
	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		str = malloc(_strlen(current_node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < index; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, current_node->str);
		str_array[index] = str;
	}
	str_array[index] = NULL;
	return (str_array);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head_ptr: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head_ptr)
{
	size_t count = 0;

	while (head_ptr)
	{
		_puts(convert_number(head_ptr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head_ptr->str ? head_ptr->str : "(nil)");
		_puts("\n");
		head_ptr = head_ptr->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @list_node: pointer to list head
 * @prefix_str: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *list_node, char *prefix_str, char next_char)
{
	char *prefix_match = NULL;

	while (list_node)
	{
		prefix_match = starts_with(list_node->str, prefix_str);
		if (prefix_match && ((next_char == -1) || (*prefix_match == next_char)))
			return (list_node);
		list_node = list_node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head_node: pointer to list head
 * @target_node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head_node, list_t *target_node)
{
	size_t index = 0;

	while (head_node)
	{
		if (head_node == target_node)
			return (index);
		head_node = head_node->next;
		index++;
	}
	return (-1);
}
