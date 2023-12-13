#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@mem_ptr: the pointer to the memory area
 *@fill_byte: the byte to fill *mem_ptr with
 *@num_bytes: the amount of bytes to be filled
 *Return: (mem_ptr) a pointer to the memory area mem_ptr
 */
char *_memset(char *mem_ptr, char fill_byte, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
		mem_ptr[i] = fill_byte;
	return (mem_ptr);
}

/**
 * ffree - frees a string of strings
 * @string_array: string of strings
 */
void ffree(char **string_array)
{
	char **current_ptr = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(current_ptr);
}

/**
 * _realloc - reallocates a block of memory
 * @prev_ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *prev_ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!prev_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(prev_ptr), NULL);
	if (new_size == old_size)
		return (prev_ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)prev_ptr)[old_size];
	free(prev_ptr);
	return (new_ptr);
}
