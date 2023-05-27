#include "shell.h"

char *err_syntax(char **argv)
{
	char *err, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(argv[0]) + 33;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": Syntax error: \"");
	_strcat(err, argv[0]);
	_strcat(err, "\" unexpected\n");

	free(hist_str);
	return (err);
}

/**
 * err_one - Creates an error message for shellby_alias errors.
 */
char *err_one(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}
