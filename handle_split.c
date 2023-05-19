#include "shell.h"

int _token_len(char *str, char *delim);
int _token_num(char *s, char *delim);

/**
 * handle_split - adds token a string.
 * @line: the string.
 * @delim: delimiter character that adds token to the string.
 * Return: A pointer to an array.
 */
char **handle_split(char *line, char *delim)
{
	char **ptr;
	int token, lett, idx, x, y;

	idx = 0;
	token = _token_num(line, delim);
	if (token == 0)
		return (NULL);
	ptr = malloc(sizeof(char *) * (token + 1));
	if (!ptr)
	{
		return (NULL);
	}
	for (x = 0; x < token; x++)
	{
		while (line[idx] == *delim)
			idx++;
		lett = _token_len(line + idx, delim);
		ptr[x] = malloc(sizeof(char) * (lett + 1));
		if (!ptr[x])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}
		for (y = 0; y < lett; y++)
		{
			ptr[x][y] = line[idx];
			idx++;
		}

		ptr[x][y] = '\0';
	}
	ptr[x] = NULL;
	return (ptr);
}

/**
 * token_len - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 */
int _token_len(char *s, char *delim)
{
	int idx, len;

	idx = len = 0;
	while (*(s + idx) && *(s + idx) != *delim)
	{
		len++;
		idx++;
	}

	return (len);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 */
int _token_num(char *s, char *delim)
{
	int idx, tokens, len;

	len = tokens = idx = 0;
	for (; *(s + idx); idx++)
		len++;

	for (idx = 0; idx < len; idx++)
	{
		if (*(s + idx) != *delim)
		{
			tokens++;
			idx += _token_len(s + idx, delim);
		}
	}

	return (tokens);
}
