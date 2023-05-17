#include "shell.h"


/**
 * main - program that run a simple UNIX command for an interpreter.
 * @argc: arguement count.
 * @argv: arguement vector.
 * Return: 0.
 */

int main(int argc, char *argv[])
{
	size_t n, idx, read;
	char *prmpt, *line, *cmd;
	int ex_val;

	line = NULL;
	prmpt = "$ ";
	if (argc != 1)
		return (exec(argv + 1));
	if (!isatty(STDIN_FILENO))
	{
		argv = clear_input(argv);
		while (argv)
		{
			exec(argv);
			argv = NULL;
			argv = clear_input(argv);
		}
		return (0);
	}
	while (1)
	{
		write(STDOUT_FILENO, prmpt, 2);
		n = 0;
		read = getline(&line, &n, stdin);
		if (read == -1)
		{
			perror("read failed\n");
			return (1);
		}
		argv = handle_split(line, " ");
		if (!argv)
		{
			perror("HAndle split failed\n");
			continue;
		}
		cmd = *argv;
		ex_val = exec(argv);
		for (idx = 1; argv[idx]; idx++)
			free(argv[idx]);
		free(argv);
		free(line);
		free(cmd);
		return (0);
	}
	return (ex_val);
}
