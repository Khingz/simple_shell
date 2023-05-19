#include "shell.h"

int create_err(char *name, int hist, char *argv, int error)
{
	char *_err;

	switch (error)
	{
		case 2:
			_err = err_2(name, hist, argv);
			break;
		case 126:
			_err = err_126(name, hist, argv);
			break;
		case 127:
			_err = err_127(name, hist, argv);
			break;
	}
	write(STDERR_FILENO, _err, strlen(error));

	if (_err)
		free(_err);
	return (error);
}
