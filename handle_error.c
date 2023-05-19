#include "shell.h"

int create_err(char *name, int hist, char **argv, int error)
{
	char *_err;

	switch (error)
	{
		case -1:
			_err = err_env(name, hist, argv);
			break;
		case 2:
			if (*(argv[0]) == 'e')
				_err = err_exit(name, hist, argv);
			else
				_err = err_cd(name, hist, argv);
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
