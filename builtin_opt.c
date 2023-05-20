#include "shell.h"

int (*_getbuiltin(char *cmd))(char **argv)
{
	builtin_t b_func[] = {
		{"exit", exit_shell},
		{ "setenv", set_env },
		{ "unsetenv", unset_env },
		{ "cd", ch_cd },
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
		if (argv[0][i] == '-')
			sign = -1;
		for (; argv[0][i]; i++)
		{
			if (argv[0][i] == '-')
				sign *= -1;

			if (argv[0][i] >= '0' && argv[0][i] <= '9')
				num = (num * 10) + (argv[0][i] - '0');
			else
				return (2);
		}
	}
	else
	{
		return (-3);
	}
	free_args(argv);
	free_env();
	exit(num * sign);
}

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int ch_cd(char **args)
{
	char *old_pwd, *pwd;
	struct stat dir;
	char **dir_inf;

	old_pwd = pwd = NULL;
	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-')
			chdir(*(get_env("OLDPWD")) + 7);
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(old_pwd);
				return (2);
			}
		}
	}
	else
		chdir(*(get_env("HOME")) + 5);

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_inf = malloc(sizeof(char *) * 2);
	if (!dir_inf)
		return (-1);

	dir_inf[0] = "OLDPWD";
	dir_inf[1] = old_pwd;
	if (set_env(dir_inf) == -1)
		return (-1);

	dir_inf[0] = "PWD";
	dir_inf[1] = pwd;
	if (set_env(dir_inf) == -1)
		return (-1);

	free(old_pwd);
	free(pwd);
	free(dir_inf);
	return (0);
}
