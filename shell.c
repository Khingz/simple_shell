#include "shell.h"


/**
 * main - program that run a simple UNIX command for an interpreter.
 * @argc: arguement count.
 * @argv: arguement vector.
 * Return: 0.
 */

int main(int argc, char *argv[])
{
	char *prmpt, *name;
	int ex_val, hist, ex_val_n;
	int *exe_ex_val;

	signal(SIGINT, handle_signal);
	hist = 1;
	prmpt = "$ ";
	name = *argv;
	ex_val = 0;
	exe_ex_val = &ex_val_n;
	exe_ex_val = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		free_env();
		return (exec(argv + 1, name, hist));
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ex_val == 0)
		{
			ex_val = handle_args(name, &hist, exe_ex_val);
			if (ex_val == -2)
				return (0);
		}
		free_env();
		return (ex_val);
	}
	while (1)
	{
		write(STDOUT_FILENO, prmpt, 2);
		ex_val = handle_args(name, &hist, exe_ex_val);
		if (ex_val == -2 || ex_val == -3)
		{
			if (ex_val == -1)
				write(STDOUT_FILENO, "\n", 1);
			free_env();
			exit(*exe_ex_val);
		}
	}
	free_env();
	return (*exe_ex_val);
}
