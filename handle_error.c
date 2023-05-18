#include "shell.h"

int create_err(char *name, int hist, char *cmd, int error)
{
	char *_err, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (error);

	len = _strlen(name) + _strlen(str_hist) + _strlen(cmd) + 6;
	if (error == 127)
		len += 10;
	else
		len += 18;
	_err = malloc(sizeof(char) * (len + 1));
	if (!_err)
		return (error);

	_strcpy(_err, name);
	_strcat(_err, ": ");
	_strcat(_err, str_hist);
	_strcat(_err, ": ");
	_strcat(_err, cmd);
	if (error == 127)
		_strcat(_err, ": not found\n");
	else
	{
		_strcat(_err, ": Permission denied\n");
	}
	write(STDERR_FILENO, _err, len);
	return (error);
}
