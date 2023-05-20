#include "shell.h"

/**
 * get_pid - Gets the current process ID.
 */
char *get_current_pid(void)
{
	size_t x;
	char *buff;
	ssize_t file;

	x = 0;
	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(file);
		return (NULL);
	}
	read(file, buff, 120);
	while (buff[x] != ' ')
		x++;
	buff[x] = '\0';

	close(file);
	return (buff);
}

/**
 * get_env_value - Gets the value corresponding to the environment variable.
 * @var: The environment variable to search for.
 */
char *get_env_val(char *proximal, int len)
{
	char *sub, *tmp, *var;
	char **var_loc;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, proximal, len);
	var_loc = get_env(var);
	free(var);
	if (var_loc)
	{
		tmp= *var_loc
		while (*tmp != '=')
			tmp++;
		tmp++;
		sub = malloc(_strlen(tmp) + 1);
		if (!sub)
			return (NULL);
		_strcpy(sub, tmp);
	}
	else
	{
		sub = NULL;
	}

	return (sub);
}

/**
 * variable_replacement - Replaces $$ with current PID, $? with the return
 * /exit value of the last program exeucted. Environment variables names
 */
void replace_var(char **line, int *exe_ex_val)
{
	int len, y, z;
	char *sub, *line_old, line_new;

	x = y = z = 0;
	sub = var = NULL;
	line_old = *line;
	for (y = 0; line_old[y]; y++)
	{
		if (line_old[y] == '$' && line_old[y + 1] &&
				line_old[y + 1] != ' ')
		{
			if (line_old[y] == '$' && line_old[y + 1])
		{
			if (line_old[y + 1] == '$')
			{
				sub = get_current_pid();
				z = y + 2;
			}
			else if (line_old[y + 1] == '?')
			{
				sub = _itoa(*exe_ex_val);
				z = y + 2;
			}
			else if (line_old[y + 1])
			{
				for (z = y + 1; line_old[z] &&
						line_old[z] != '$' &&
						line_old[z] != ' '; z++)
					;
				len = z - (y + 1);
				sub = get_env_val(&line_old[y + 1], len);
			}
			line_new = malloc(y + _strlen(sub) + _strlen(&line_old[z]) + 1);
			if (!line_new)
				return;
			line_new[0] = '\0';
			_strncat(line_new, line_old, y);
			if (sub)
			{
				_strcat(line_new, sub);
				free(sub);
				sub = NULL;
			}
			_strcat(line_new, &line_old[z]);
			free(line_old);
			*line = line_new;
			line_new = line_new;
			y = -1;
		}
	}
}

/**
 * free_args - Free up memory taken by args.
 */
void free_args(char **args)
{
	size_t x;

	x = 0;
	while (args[x])
	{
		free(args[x];
		x++;
	}
	free(args);
}
