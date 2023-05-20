#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *tmp_ptr, *filler;
	unsigned int idx;
	void *memory;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		memory = malloc(new_size);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	tmp_ptr = ptr;
	memory = malloc(sizeof(*tmp_ptr) * new_size);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = memory;

	for (idx = 0; idx < old_size && idx < new_size; idx++)
		filler[idx] = *tmp_ptr++;

	free(ptr);
	return (memory);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 */
void reassign_lineptr(char **lineptr, size_t *n, char *buff, size_t x)
{
	if (*lineptr == NULL)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		*lineptr = buff;
	}
	else if (*n < x)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		free(*lineptr);
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}

/**
 * _getline - Reads input from a stream.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	reassign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
