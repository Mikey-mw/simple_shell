#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info_ptr: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info_ptr, char *file_path)
{
	struct stat file_stat;

	(void)info_ptr;
	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_str: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_str, int start_index, int stop_index)
{
	static char buffer[1024];
	int new_index = 0, k = 0;

	for (k = 0, new_index = start_index; new_index < stop_index; new_index++)
		if (path_str[new_index] != ':')
			buffer[k++] = path_str[new_index];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info_ptr: the info struct
 * @path_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info_ptr, char *path_str, char *cmd)
{
	int index = 0, current_pos = 0;
	char *full_path;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info_ptr, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[index] || path_str[index] == ':')
		{
			full_path = dup_chars(path_str, current_pos, index);
			if (!*full_path)
				_strcat(full_path, cmd);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, cmd);
			}
			if (is_cmd(info_ptr, full_path))
				return (full_path);
			if (!path_str[index])
				break;
			current_pos = index;
		}
		index++;
	}
	return (NULL);
}
