#include "shell.h"

void space_handler(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char previous, current, next;
	size_t i, j;
	ssize_t new_len = 0;

	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (current == '#')
		{
			if ((i == 0 && next != '!') || old_line[i - 1] == ' ')
			{
				old_line[i] = '\0';
				break;
			}
		}
		else if (current == ';')
		{
				if (i != 0 && old_line[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
		}
		else if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_len++;
				else if (previous == '&' && next != ' ')
					new_len++;
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_len++;
				else if (previous == '|' && next != ' ')
					new_len++;
			}
		}
		new_len++;
	}
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;

	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ')
				new_line[j++] = ' ';
			continue;
		}
		else if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	printf("new line [%s]\n", new_line);
	exit(0);
	free(*line);
	*line = new_line;
}
