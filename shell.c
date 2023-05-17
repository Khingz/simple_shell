#include "shell.h"


/**
 * main - program that run a simple UNIX command for an interpreter.
 * @argc: arguement count.
 * @argv: arguement vector.
 * Return: 0.
 */

int main(void)
{
	pid_t pid;
	int status;
	char **arg_v;
	size_t n, index, read;
	char *line, *prmpt;

	line = NULL;
	prmpt = "$ ";
	while (1)
	{
		write(STDOUT_FILENO, prmpt, 2);
		n = 0;
		if ((read = getline(&line, &n, stdin)) == -1)
		{
			perror("read failed\n");
			return (1);
		}
		arg_v = _strtok(line, " ");
		if (*arg_v[0] != '/')
			*arg_v = get_location(*arg_v);
		pid = fork();
		if (pid == -1)
		{
			perror("Error child:");
			return (1);
		}
		if (pid == 0)
		{
			if (execve(*arg_v, arg_v, NULL) == -1)
				perror("Error exec gone wrong:");
		}
		else
		{
			wait(&status);
		}
		for (idx = 0; arg_v[idx]; idx++)
			free(argv[idx]);
		free(arg_v);
		free(line);
		return (0);
	}
	return (0);
}
