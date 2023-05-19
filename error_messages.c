#include "shell.h"

char *error_126(char *name, int hist, char **argv)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = strlen(name) + 2 + strlen(hist_str) + 2 + strlen(argv[0]) + 2 +
		18;
	error = malloc(sizeof(char) * (len + 1));

	if (!error)
		return (NULL);

	strcpy(error, name);
	strcat(error, ": ");
	strcat(error, hist_str);
	strcat(error, ": ");
	strcat(error, argv[0]);
	strcat(error, ": ");
	strcat(error, "Permission denied\n");

	return (error);
}

char *error_127(char *name, int hist, char **argv)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = strlen(name) + 2 + strlen(hist_str) + 2 + strlen(argv[0]) + 2 +
		10;
	error = malloc(sizeof(char) * (len + 1));

	if (!error)
		return (NULL);

	strcpy(error, name);
	strcat(error, ": ");
	strcat(error, hist_str);
	strcat(error, ": ");
	strcat(error, argv[0]);
	strcat(error, ": ");
	strcat(error, "not found\n");

	return (error);
}

char *err_2(char *name, int hist, char **argv)
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
		return (NULL);

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": ");
	_strcat(err, *argv);
	_strcat(err, ": ");
	_strcat(err, "Illegal Number");
	_strcat(err, ": ");
	_strcat(err, argv[1]);
	_strcat(err, "\n");

	return (err);
}
