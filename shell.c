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
	char *prmpt, *line, *cmd, *name;
	int ex_val, hist;

	line = NULL;
	hist = 1;
	prmpt = "$ ";
	name = *argv;
	if (argc != 1)
		return (exec(argv + 1, name, hist));
	if (!isatty(STDIN_FILENO))
	{
		argv = clear_input(argv);
		while (argv)
		{
			cmd = *argv;
			ex_val = exec(argv, name, hist);
			hist++;
			for (idx = 1; argv[idx]; idx++)
				free(argv[idx]);
			free(argv);
			free(cmd);
			argv = NULL;
			argv = clear_input(argv);
		}
		return (ex_val);
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
		cmd = argv[0];
		ex_val = exec(argv, name, hist);
		hist++;
		for (idx = 1; argv[idx]; idx++)
			free(argv[idx]);
		free(argv);
		free(line);
		free(cmd);
		return (ex_val);
	}
	return (ex_val);
}
