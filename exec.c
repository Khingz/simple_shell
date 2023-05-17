#include "shell.h"

int exec(char **arg)
{
	pid_t pid_child;
	int status, flag;

	flag = 0;
	if (*arg[0] != '/')
	{
		flag = 1;
		*arg = get_loc(*arg);
	}

	pid_child = fork();
	if (pid_child == -1)
	{
		if (flag)
			free(*arg);
		perror("Error child:");
		return (1);
	}
	if (pid_child == 0)
	{
		if (execve(*arg, arg, NULL) == -1)
			perror("Error executing");
	}
	else
	{
		wait(&status);
	}

	if (flag)
		free(*arg);
	return (0);
}

char **clear_input(char **argv)
{
	ssize_t read, n;
	char *line_ptr;

	read = getline(&line_ptr, &n, stdin);
	if (read == -1)
		return (NULL);

	argv = handle_split(line_ptr, " ");

	return (argv);
}
