#include "shell.h"

/**
 * handle_split - adds token a string.
 * @line: the string.
 * @delim: delimiter character that adds token to the string.
 * Return: A pointer to an array.
 */
char **handle_split(char *line, char *delim)
{
	char **ptr;
	int idx;
	char *token;
	size_t word_num;

	word_num = 0;
	for (idx = 0; line[idx]; idx++)
	{
		if (line[idx] != *delim && (line[idx + 1] == *delim || line[idx + 1] == '\0'))
				word_num++;
	}
	line[idx - 1] = '\0';
	ptr = malloc(sizeof(char *) * (word_num + 1));
	if (!ptr)
	{
		return (NULL);
	}
	token = strtok(line, delim);
	for (idx = 0; token != NULL; idx++)
	{
		ptr[idx] = malloc(_strlen(token) + 1);
		if (!ptr[idx])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}
		_strcpy(ptr[idx], token);
		token = strtok(NULL, delim);
	}
	ptr[idx] = NULL;
	return (ptr);
}
