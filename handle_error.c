#include "shell.h"

int create_err(char *name, int hist, char *argv, int error)
{
	char *_err;

	switch (error)
	{
		case -1:
			_err = err_env(name, hist, args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				error = error_2(name, hist, args);
			else
				error = error_2cd(name, hist, args);
			break;
		case 126:
			_err = err_126(name, hist, argv);
			break;
		case 127:
			_err = err_127(name, hist, argv);
			break;
	}
	write(STDERR_FILENO, _err, strlen(_err));

	if (_err)
		free(_err);
	return (error);
}
