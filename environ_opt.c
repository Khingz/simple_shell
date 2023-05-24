#include "shell.h"

/**
 * get_env - Gets an env variable from the PATH.
 * @name: name of the env variable to get.
 * Return: pointer to env or NULL.
 */
char **_get_env(const char *name)
{
	int len, idx;

	len = _strlen(name);
	for (idx = 0; environ[idx]; idx++)
	{
		if (_strncmp(name, environ[idx], len) == 0)
			return (&environ[idx]);
	}
	return (NULL);
}

/**
 * copy_env - make a copy of the env.
 * Return: ponter ro copied or NULL
 */
char **_copy_env(void)
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
		new_env[idx] = malloc(_strlen(environ[idx]) + 1);
		if (!new_env[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(new_env[idx]);
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
