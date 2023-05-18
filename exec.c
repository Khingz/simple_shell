#include "shell.h"

int exec(char **arg, char *name, int hist)
{
	pid_t pid_child, ex_val;
	int status, flag;
	char *cmd;
       
	cmd = *arg;
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
		{
			create_err(name, hist, cmd, 1);
			return (127);
		}
	}
	else
	{
		wait(&status);
		ex_val = WEXITSTATUS(status);
	}

	if (flag)
		free(*arg);
	return (ex_val);
}

char **clear_input(char **argv)
{
	ssize_t read, n;
	char *line_ptr;

	read = getline(&line_ptr, &n, stdin);
	if (read == -1)
	{
		free(line_ptr);
		return (NULL);
	}

	argv = handle_split(line_ptr, " ");
	free(line_ptr);
	return (argv);
}
