#include "shell.h"

int (*_getbuiltin(char *cmd))(char **argv, char **begin)
{
	builtin_t b_func[] = {
		{"exit", exit_shell},
		{ "setenv", set_env },
		{ "unsetenv", unset_env },
		{ "cd", ch_cd },
		{"env", print_env},
		{"alias", _alias},
		{"help", builtin_help},
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

int exit_shell(char **argv, char **begin)
{
	int i = 0, int_len = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (argv[0])
	{
		for (; argv[0][i]; i++)
		{
			if (i <= int_len && argv[0][i] >= '0' && argv[0][i] <= '9')
				num = (num * 10) + (argv[0][i] - '0');
			else
				return (create_err(--argv, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max -1)
		return (create_err(--argv, 2));
	argv -= 1;
	free_args(argv, begin);
	free_env();
	free_aliase_list(aliases);
	exit(num);
}

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int ch_cd(char **args, char __attribute__((__unused__)) **begin)
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
				return (create_err(args, 2));
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
	if (set_env(dir_inf, dir_inf) == -1)
		return (-1);

	dir_inf[0] = "PWD";
	dir_inf[1] = pwd;
	if (set_env(dir_inf, dir_inf) == -1)
		return (-1);

	free(old_pwd);
	free(pwd);
	free(dir_inf);
	return (0);
}

/**
 * shellby_help - Displays information about shellby builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int builtin_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
