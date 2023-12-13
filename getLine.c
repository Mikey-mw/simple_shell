#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @buffer_length: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buffer, size_t *buffer_length)
{
	ssize_t bytes_read = 0;
	size_t buffer_size = 0;

	if (!*buffer_length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->command_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &buffer_size, stdin);
#else
		bytes_read = _getline(info, buffer, &buffer_size);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*buffer_length = bytes_read;
				info->command_buffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input_line - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input_line(info_t *info)
{
	static char *command_buffer; /* the ';' command chain buffer */
	static size_t i, j, buffer_length;
	ssize_t bytes_read = 0;
	char **command_buffer_ptr = &(info->input_arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = buffer_chained_commands(info, &command_buffer, &buffer_length);
	if (bytes_read == -1) /* EOF */
		return (-1);
	if (buffer_length)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buffer position */
		p = command_buffer + i; /* get pointer for return */

		check_chain(info, command_buffer, &j, i, buffer_length);
		while (j < buffer_length) /* iterate to semicolon or end */
		{
			if (is_chain(info, command_buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= buffer_length) /* reached end of buffer? */
		{
			i = buffer_length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*command_buffer_ptr = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*command_buffer_ptr = command_buffer; /* else not a chain, pass back buffer */
	return (bytes_read); /* return length of buffer from _getline() */
}

/**
 * read_input_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @length: size
 *
 * Return: r
 */
ssize_t read_input_buf(info_t *info, char *buf, size_t *length)
{
	ssize_t bytes_read = 0;

	if (*length)
		return (0);
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*length = bytes_read;
	return (bytes_read);
}

/**
 * _getline_input - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline_input(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, buffer_length;
	size_t k;
	ssize_t bytes_read = 0, total_size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		total_size = *length;
	if (i == buffer_length)
		i = buffer_length = 0;

	bytes_read = read_input_buf(info, buf, &buffer_length);
	if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : buffer_length;
	new_p = _realloc(p, total_size, total_size ? total_size + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (total_size)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	total_size += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = total_size;
	*ptr = p;
	return (total_size);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
