#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *tmp_ptr, *filler;
	unsigned int idx;
	void *memory;

	if (new_size == prev_size)
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

	for (idx = 0; idx < prev_size && idx < new_size; idx++)
		filler[idx] = *tmp_ptr++;

	free(ptr);
	return (memory);
}

/**
 * assign_lineptr - Reassigns the lineptr variable for _getline.
 */
void reassign_lineptr(char **line_ptr, size_t *n, char *buff, size_t x)
{
	if (*line_ptr == NULL)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		*line_ptr = buff;
	}
	else if (*n < x)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		free(*line_ptr);
		*line_ptr = buff;
	}
	else
	{
		_strcpy(*line_ptr, buff);
		free(buff);
	}
}

/**
 * _getline - Reads input from a stream.
 */
ssize_t _getline(char **line_ptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ex_val;
	char ch;
	char *buff;
	int b_read;

	ch = 'x';
	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (ch != '\n')
	{
		b_read = read(STDIN_FILENO, &ch, 1);
		if (b_read == -1 || (b_read == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (b_read == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buff = _realloc(buff, input, input + 1);

		buff[input] = ch;
		input++;
	}
	buff[input] = '\0';

	reassign_lineptr(line_ptr, n, buff, input);

	ex_val = input;
	if (b_read != 0)
		input = 0;
	return (ex_val);
}
