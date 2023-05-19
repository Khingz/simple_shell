#include "shell.h"

/**
 * get_env - Gets an env variable from the PATH.
 * @name: name of the env variable to get.
 * Return: pointer to env or NULL.
 */
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

/**
 * set_env -  sets an env variable to the PATH.
 * @name: name of the env variable to change or add.
 * @val: value of the env variable to change or add.
 * @o_write: flag indicating if the variable should be overwritten.
 * Return: -1 or - 0.
 */
int set_env(const char *name, const char *val, int o_write)
{
	char *env_var, *new_val;
	char **new_env;
	int idx;
	size_t name_len, value_len, size;

	env_var = get_env(name);
	name_len = _strlen(name);
	value_len = _strlen(val);
	new_val = malloc(name_len + 1 + value_len + 1);
	_strcpy(new_val, name);
	_strcat(new_val, "=");
	_strcat(new_val, val);

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

	for (idx = 0; environ[idx]; idx++)
	{
		new_env[dx] = environ[idx];
	}
	free(environ);
	environ = new_env;
	env_var = get_env(name);
	if (env_var && o_write)
	{
		env_var = new_val;
		return (0);
	}
	environ[idx] = new_val;
	environ[idx + 1] = NULL;
	return (0);
}

/**
 * unset_env - del an env variable from the PATH.
 * @name: name of the env variable to delete.
 * Return: -1 or -0.
 */
int unset_env(const char *name)
{
	char **new_env;
	size_t size;
	int idx_1, idx_2;
	char *env_var;

	env_var = get_env(name);
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
		{
			free(env_var);
			continue;
		}
		idx_2++;
	}
	free(environ);
	environ = new_env;
	environ[size - 1] = NULL;
	return (0);
}

/**
 * copy_env - make a copy of the env.
 * Return: ponter ro copied or NULL
 */
char **copy_env(void)
{
	char **new_env;
	size_t size;
	int idx;

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (idx = 0; environ[idx]; idx++)
	{
		new_env[idx] = malloc(_strlen(env[idx] + 1));
		if (!new_env[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(new_envn[idx]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[idx], environ[idx]);
	}
	new_env[idx] = NULL;
	return (new_env);
}

/**
 * free_env - Frees the the env copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}
