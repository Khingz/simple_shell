#include "shell.h"

void create_err(char *name, int hist, char *cmd, int error)
{
	char *_err, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return;

	len = _strlen(name) + _strlen(str_hist) + _strlen(cmd) + 16;
	_err = malloc(sizeof(char) * (len + 1));
	if (!_err)
		return;

	_strcpy(_err, name);
	_strcat(_err, ": ");
	_strcat(_err, str_hist);
	_strcat(_err, ": ");
	_strcat(_err, cmd);
	_strcat(_err, ": not found\n");

	write(STDERR_FILENO, _err, len);
	(void)error;
}
