#include "shell.h"

/**
 * shellby_env - Prints the current environment where each line is a different
 * variable in the format, 'variable'='value'.
 * @args: A double pointer for the args passed to shell.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 */
//shellvy_env
int print_env(char **args)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);
	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}
	(void)args;
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
int set_env(char **args)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[1] || !args[2])
		return (-1);
	new_value = malloc(_strlen(args[1]) + 1 + _strlen(args[2]) + 1);
	if (!new_value)
		return (-1);
	_strcpy(new_value, args[1]);
	_strcat(new_value, "=");
	_strcat(new_value, args[2]);

	env_var = _getenv(args[1]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (-1);
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;

	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: A double pointer where args[1] points to the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unset_env(char **args)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[1])
		return (-1);
	env_var = _getenv(args[1]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (-1);

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int ch_cd(char **args)
{
	char *old_pwd, *pwd;
	struct stat dir;

	old_pwd = pwd = NULL
	old_pwd = get_cwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (args[1])
	{
		if (*(args[1]) == '-')
			chdir(*(get_env("OLDPWD")) + 7);
		else
		{
			if (stat(args[1], &dir) == 0 && S_ISDIR(dir.st_mode))
				chdir(args[1]);
			else
			{
				free(old_pwd);
				return (2);
			}
		}
	}
	else
		chdir(*(get_env("HOME")) + 5);

	pwd = get_cwd(pwd, 0);
	if (!pwd)
		return (-1);

	set_env("OLDPWD", oldpwd, 1);
	set_env("PWD", pwd, 1);

	free(old_pwd);
	free(pwd);
	return (0);
}
