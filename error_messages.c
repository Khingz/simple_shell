#include "shell.h"

char *err_126(char *name, int hist, char **argv)
{
	char *err, *str_his;
	int len;

	str_his = _itoa(hist);
	if (!str_his)
		return (NULL);

	len = _strlen(name) + 2 + _strlen(str_his) + 2 + _strlen(*argv) + + 18;
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
		return (NULL);

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": ");
	_strcat(err, *argv);
	_strcat(err, ": ");
	_strcat(err, "Permission denied\n");

	return (err);
}

char *err_127(char *name, int hist, char **argv)
{
	char *err, *str_his;
	int len;

	str_his = _itoa(hist);
	if (!str_his)
		return (NULL);

	len = _strlen(name) + 2 + _strlen(str_his) + 2 + _strlen(*argv) + 2 + 10
	err = malloc(sizeof(char) * (len + 1));

	if (!err)
		return (NULL);

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, str_his);
	_strcat(err, ": ");
	_strcat(err, *argv);
	_strcat(err, ": ");
	_strcat(err, "not found\n");

	return (err);
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
