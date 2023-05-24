#include "shell.h"

char *err_126(char **argv)
{
	char *err, *str_his;
	int len;

	str_his = _itoa(hist);
	if (!str_his)
		return (NULL);

	len = _strlen(name) + _strlen(str_his) + _strlen(*argv) + 24;
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": ");
	_strcat(err, *argv);
	_strcat(err, ": ");
	_strcat(err, "Permission denied\n");

	free(str_his);
	return (err);
}

char *err_127(char **argv)
{
	char *err, *str_his;
	int len;

	str_his = _itoa(hist);
	if (!str_his)
		return (NULL);

	len = _strlen(name) + 2 + _strlen(str_his) + 2 + _strlen(*argv) + 2 + 10;
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": ");
	_strcat(err, *argv);
	_strcat(err, ": ");
	_strcat(err, "not found\n");

	free(str_his);
	return (err);
}


char *err_exit(char **argv)
{
	char *err, *str_his;
	int len;

	str_his = _itoa(hist);
	if (!str_his)
		return (NULL);

	len = _strlen(name) + 2 + _strlen(str_his) + 2 + _strlen(*argv) + 2 +
		14 + 2 + _strlen(argv[1]) + 1;
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": exit: Illegal Number: ");
	_strcat(err, ": ");
	_strcat(err, argv[0]);
	_strcat(err, "\n");

	free(str_his);
	return (err);
}

char *err_env(char **argv)
{
	char *err, *str_his;
	int len;

	str_his = _itoa(hist);
	if (!str_his)
		return (NULL);

	len = _strlen(name) + _strlen(str_his) + _strlen(*argv) + 45;
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": ");
	_strcat(err, *argv);
	_strcat(err, "Unable to add/remove from environment\n");

	free(str_his);
	return (err);
}

char *err_cd(char **argv)
{
	char *err, *str_his;
	int len;

	str_his = _itoa(hist);
	if (!str_his)
		return (NULL);

	len = _strlen(name) + _strlen(str_his) + _strlen(*argv) + _strlen(argv[1]) + 21;
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": cd: can't cd to");
	_strcat(err, *argv);
	_strcat(err, "Can't cd");
	_strcat(err, "\n");

	free(str_his);
	return (err);
}
