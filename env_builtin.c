#include "shell.h"

/**
 * shellby_env - Prints the current environment where each line is a different
 */
int print_env(char **argv, char __attribute__((__unused__)) **begin)
{
	int idx;
	char nc = '\n';

	if (!environ)
		return (-1);
	for (idx = 0; environ[idx]; idx++)
	{
		write(STDOUT_FILENO, environ[idx], _strlen(environ[idx]));
		write(STDOUT_FILENO, &nc, 1);
	}
	(void)argv;
	return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @args: A double pointer where args[1] points to the name of the new or
 * existing PATH variable. args[2] points to the value of the to set for the
 * new or PATH variable.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int set_env(char **argv, char __attribute__((__unused__)) **begin)
{
	char **env_var, *new_val;
	size_t size;
	int idx;
	char **new_env;

	env_var = NULL;
	if (!argv[0] || !argv[1])
		return (-1);
	new_val = malloc(_strlen(argv[0]) + 1 + _strlen(argv[1]) + 1);
	if (!new_val)
		return (-1);
	_strcpy(new_val, argv[0]);
	_strcat(new_val, "=");
	_strcat(new_val, argv[1]);

	env_var = _get_env(argv[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_val);
		return (-1);
	}

	for (idx = 0; environ[idx]; idx++)
		new_env[idx] = environ[idx];

	free(environ);
	environ = new_env;
	environ[idx] = new_val;
	environ[idx + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: A double pointer where args[1] points to the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unset_env(char **argv, char __attribute__((__unused__)) **begin)
{
	char **env_var, **new_env;
	size_t size;
	int idx, idx2;

	if (!argv[0])
		return (-1);
	env_var = _get_env(argv[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (-1);

	for (idx = 0, idx2 = 0; environ[idx]; idx++)
	{
		if (*env_var == environ[idx])
		{
			free(*env_var);
			continue;
		}
		new_env[idx2] = environ[idx];
		idx2++;
	}
	free(environ);
	environ = new_env;
	environ[size - 1] = NULL;

	return (0);
}
