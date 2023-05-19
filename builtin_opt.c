#include "shell.h"

int (*_getbuiltin(char *cmd))(char **argv)
{
	builtin_t b_func[] = {
		{"exit", shellby_exit},
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{NULL, NULL}
	};
	int i;

	for (i = 0; b_func[i].name; i++)
	{
		if (_strcmp(b_func[i].name, cmd) == 0)
			break;
	}
	return (b_func[i].f);
}

int exit_shell(char **argv)
{
	int i = 0, sign = 1;
	unsigned int num = 0;

	if (argv[1])
	{
		if (argv[1][i] == '-')
			sign = -1;
		for (; argv[1][i]; i++)
		{
			if (argv[1][i] == '-')
				sign *= -1;

			if (argv[1][i] >= '0' && argv[1][i] <= '9')
				num = (num * 10) + (argv[1][i] - '0');
			else
				return (2);
		}
	}
	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
	free_env();
	exit(num * sign);
}
