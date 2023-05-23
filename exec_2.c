#include "shell.h"

/**
 * run_args - Calls the execution of a command
 */
int _run_args(char **argv, char **begin, int *exe_ex_val)
{
	int ex_val, i;
	int (*builtin)(char **args, char **begin);

	builtin = _getbuiltin(argv[0]);
	if (builtin)
	{
		ex_val = builtin(argv + 1, begin);
		if (ex_val != EXIT)
			*exe_ex_val = ex_val;
	}
	else
	{
		*exe_ex_val = exec(argv, begin);
		ex_val = *exe_ex_val;
	}

	hist++;

	for (i = 0; argv[i]; i++)
		free(argv[i]);

	return (ex_val);
}

/**
 * handle_line - Partitions a line read from standard input as needed.
 */
void _handle_line(char **line, ssize_t read)
{
	char *line_old, *line_new;
	char curr, next, prev;
	size_t i, j;
	ssize_t len;

	len = _get_new_len(*line);
	if (len == read - 1)
		return;
	line_new = malloc(len + 1);
	if (!line_new)
		return;
	j = 0;
	line_old = *line;
	for (i = 0; line_old[i]; i++)
	{
		curr = line_old[i];
		next = line_old[i + 1];
		if (i != 0)
		{
			prev = line_old[i - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					line_new[j++] = ' ';
					line_new[j++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					line_new[j++] = ';';
					line_new[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					line_new[j++] = ' ';
				line_new[j++] = ';';
				if (next != ' ')
					line_new[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					line_new[j++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					line_new[j++] = '&';
					line_new[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					line_new[j++] = ' ';
				else if (prev == '|' && next != ' ')
				{
					line_new[j++] = '|';
					line_new[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && line_new[i - 1] != ' ')
				line_new[j++] = ' ';
			line_new[j++] = ';';
			if (next != ' ')
				line_new[j++] = ' ';
			continue;
		}
		line_new[j++] = line_old[i];
	}
	line_new[j] = '\0';

	free(*line);
	*line = line_new;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#"
 */

ssize_t _get_new_len(char *line)
{
	size_t i;
	ssize_t len = 0;
	char curr, next;

	for (i = 0; line[i]; i++)
	{
		curr = line[i];
		next = line[i + 1];
		if (curr == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					len++;
				if (next != ' ')
					len++;
			}
			else
				logical_ops(&line[i], &len);
		}
		else if (curr == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				len++;
			if (next != ' ')
				len++;
		}
		len++;
	}
	return (len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}

