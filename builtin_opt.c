#include "shell.h"

/**
  * _getbuiltin: a func description for the following arguement.
  * @cmd: a string
  * @argv: a pointer to a string
  * @begin: a pointer
  * Return: NULL
**/
int (*_getbuiltin(char *cmd))(char **argv, char **begin)
{
	builtin_t b_func[] = {
		{"exit", exit_shell},
		{ "setenv", set_env },
		{ "unsetenv", unset_env },
		{ "cd", ch_cd },
		{"env", print_env},
		{"alias", _alias},
		{"help", _help_builtin},
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

/**
  * exist_shell- func description for the arguements below
  * @argv: an array pointing to a string
  * @begin: a pointer to a string
  * Return: NULL
**/
int exit_shell(char **argv, char **begin)
{
	int i = 0, int_len = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (argv[0])
	{
		if (argv[0][0] == '+')
		{
			i = 1;
			int_len++;
		}
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
	if (num > max - 1)
		return (create_err(--argv, 2));
	argv -= 1;
	free_args(argv, begin);
	free_env();
	free_aliase_list(aliases);
	exit(num);
}

/**
 * ch_cd - func that changes the current directory of the shellby process.
 * @args: array of the arguments.
 * @begin: a pointer.
 * Return: If the given string is not a directory - 2 or -1 or 0.
 **/
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
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_get_env("OLDPWD") != NULL)
					(chdir(*_get_env("OLDPWD") + 7));
			}
			else
			{
				free(old_pwd);
				return (create_err(args, 2));
			}
		}
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
	{
		if (_get_env("HOME") != NULL)
			chdir(*(_get_env("HOME")) + 5);
	}

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
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(old_pwd);
	free(pwd);
	free(dir_inf);
	return (0);
}

/**
 * _help_builtin - func that displays information about builtin commands.
 * @argv: array pointing to the arguments.
 * @begin: pointer to the beginning of argv.
 * Return: returns -1 or -0 on error.
 */
int _help_builtin(char **argv, char __attribute__((__unused__)) **begin)
{
	if (!argv[0])
		general_help();
	else if (_strcmp(argv[0], "alias") == 0)
		aliase_help();
	else if (_strcmp(argv[0], "cd") == 0)
		cd_help();
	else if (_strcmp(argv[0], "exit") == 0)
		exit_help();
	else if (_strcmp(argv[0], "env") == 0)
		env_help();
	else if (_strcmp(argv[0], "setenv") == 0)
		set_env_help();
	else if (_strcmp(argv[0], "unsetenv") == 0)
		unset_env_help();
	else if (_strcmp(argv[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
