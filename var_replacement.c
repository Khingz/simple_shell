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
char *get_env_val(char *var)
{
	char *sub, *tmp;
	char **var_loc;

	var_loc = get_env(var);

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
void replace_var(char **args, int *exe_ex_val)
{
	int len, x, y, z;
	char *var, *sub, *line;

	x = y = z = 0;
	sub = var = line = NULL;
	for (x = 0; args[x]; x++)
	{
		for (y = 0; args[x][y]; y++)
		{
			if (args[x][y] == '$' && args[x][y + 1])
			{
				if (args[x][y + 1] == '$')
				{
					sub = get_pid();
					z = y + 2;
				}
				else if (args[x][y + 1] == '?')
				{
					sub = _itoa(exe_ex_val);
					z = y + 2;
				}
				else if (args[x][y + 1])
				{
					for (z = y + 1; args[x][z] && args[x][z] != '$'; z++)
						;
					len = z - (y + 1);
					var = malloc(len + 1);
					if (!var)
						return;
					var[0] = '\0';
					_strncat(var, &args[i][j + 1], len);
					sub = get_env_val(var);
					free(var);
				}
				line = malloc(y + _strlen(sub) + _strlen(&args[x][z]) + 1);
				if (!line)
					return;
				line[0] = '\0';
				_strncat(line, args[x], y);
				if (sub)
				{
					_strcat(line, sub);
					free(sub);
					sub = NULL;
				}
				_strcat(line, &args[x][z]);
				free(args[x]);
				args[x] = line;
				y = -1;
			}
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
