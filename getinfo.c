#include "shell.h"

/**
 * initialize_shell_info - initializes info_t struct
 * @info: struct address
 */
void initialize_shell_info(info_t *info)
{
	info->input_arg = NULL;
	info->argument_vector = NULL;
	info->executable_path = NULL;
	info->argument_count = 0;
}

/**
 * populate_shell_info - initializes info_t struct
 * @info: struct address
 * @argument_vector: argument vector
 */
void populate_shell_info(info_t *info, char **argument_vector)
{
	int i = 0;

	info->program_name = argument_vector[0];
	if (info->input_arg)
	{
		info->argument_vector = strtow(info->input_arg, " \t");
		if (!info->argument_vector)
		{

			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->input_arg);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * release_shell_info - frees info_t struct fields
 * @info: struct address
 * @free_all: true if freeing all fields
 */
void release_shell_info(info_t *info, int free_all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->executable_path = NULL;
	if (free_all)
	{
		if (!info->command_buffer)
			free(info->input_arg);
		if (info->env_list)
			free_list(&(info->env_list));
		if (info->history_list)
			free_list(&(info->history_list));
		if (info->alias_list)
			free_list(&(info->alias_list));
		ffree(info->environment);
		info->environment = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
