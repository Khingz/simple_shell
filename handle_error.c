#include "shell.h"

int create_err(char **argv, int error)
{
	char *_err;

	switch (error)
	{
		case -1:
			_err = err_env(argv);
			break;
		case 1:
			_err = err_env(argv);
			break;
		case 2:
			if (*(argv[0]) == 'e')
				_err = err_exit(++argv);
			else if (argv[0][0] == ';' || argv[0][0] == '&' || argv[0][0] == '|')
				_err = err_syntax(argv);
			else
				_err = err_cd(argv);
			break;
		case 126:
			_err = err_126(argv);
			break;
		case 127:
			_err = err_127(argv);
			break;
	}
	write(STDERR_FILENO, _err, _strlen(_err));

	if (_err)
		free(_err);
	return (error);
}
