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
	int ex_val, hist;

	hist = 1;
	prmpt = "$ ";
	name = *argv;
	if (argc != 1)
		return (exec(argv + 1, name, hist));
	if (!isatty(STDIN_FILENO))
	{
		argv = clear_input(argv);
		while (ex_val != -1)
		{
			ex_val = execute_args(argv, name, &hist);
		}
		return (0);
	}
	while (1)
	{
		write(STDOUT_FILENO, prmpt, 2);
		ex_val = execute_args(argv, name, &hist);
		if (ex_val == -1)
		{
			perror("HAndle split failed\n");
		}
	}
	return (ex_val);
}
