#include "shell.h"

extern char **environ;

char *get_env(const char *name)
{
	int len, idx;

	len = _strlen(name);
	for (idx = 0; environ[idx]; idx++)
	{
		if (_strncmp(name, environ[idx], len) == 0)
			return (environ[idx]);
	}
	return (NULL);
}

int set_env(const char *name, const char *val, int o_write)
{
	char *env_var, new_val;
	char **new_env;
	int idx_1, idx_2;
	size_t name_len, value_len, size;

	env_var = _getenv(name);
	name_len = _strlen(name);
	value_len = _strlen(value);
	new_val = malloc(name_len + 1 + value_len + 1);
	for (idx_1 = 0; name[idx_1]; idx_1++)
		new_val[idx] = name[idx];
	new_val[idx++] = '=';
	for (idx_2 = 0; val[idx_2]; idx_1++, idx_2++)
		new_val[idx_1] = value[idx_2];
	new_val[idx_1] = '\0';

	for (size = 0; environ[size]; size++)
		;
	if (env_var)
		new_env = malloc(sizeof(char *) * (size + 1));
	else
		new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_val);
		return (-1);
	}

	for (idx_1 = 0; environ[idx_1]; idx_1++)
	{
		new_env[idx_1] = malloc(_strlen(environ[idx_1] + 1));
		if (!new_env[idx_1])
		{
			for(idx_1--; idx_1 >= 0; idx_1--)
				free(new_env[idx_1]);
			free(new_env);
			free(new_val);
			return (-1);
		}
		_strcpy(new_env[idx_1], environ[idx_1]);
	}
	environ = new_env;
	env_var = _getenv(name);
	if (env_var && o_write)
	{
		env_var = new_val;
		return (0);
	}
	environ[idx_1] = new_val;
	environ[idx_1 + 1] = NULL;
	return (0);
}

int unset_env(const char *name)
{
	char **new_env;
	size_t size;
	int index, index2;
	char *env_var;

	env_var = _getenv(name);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (-1);

	for (idx_1 = 0, idx_2 = 0; environ[idx_1]; idx_1++)
	{
		if (env_var == environ[idx_1])
			continue;
		new_env[idx_2] = malloc(strlen(environ[idx_1] + 1));
		if (!new_env[idx_2])
		{
			for(idx_2--; idx_2 >= 0; idx_2--)
				free(new_env[idx_2]);
			free(new_env);
			return (-1);
		}
		_strcpy(new_env[idx_2], environ[idx_1]);
		idx_2++;
	}
	environ = new_env;
	environ[size - 1] = NULL;
	return (0);
}
