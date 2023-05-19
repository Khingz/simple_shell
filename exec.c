#include "shell.h"

int exec(char **arg, char *name, int hist)
{
	pid_t pid_child, ex_val;
	int status, flag;
	char *cmd;
       
	cmd = *arg;
	flag = 0;
	if (*cmd != '.' && *cmd != '/')
	{
		flag = 1;
		cmd = get_loc(cmd);
	}

	pid_child = fork();
	if (pid_child == -1)
	{
		if (flag)
			free(cmd);
		perror("Error child:");
		return (1);
	}
	if (pid_child == 0)
	{
		if (!cmd || (access(cmd, F_OK) == -1))
			return(create_err(name, hist, *arg, 127));
		if (access(cmd, X_OK) == -1)
			return (create_err(name, hist, *arg, 126));
		if (execve(cmd, arg, NULL) == -1)
		{
			perror("EEEEEEEEERRRRROO");
		}
	}
	else
	{
		wait(&status);
		ex_val = WEXITSTATUS(status);
	}

	if (flag)
		free(cmd);
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

//run_args
int execute_args(char **argv, char *name, int *hist)
{
	int idx, ex_val;

	argv = _get_args(argv);
	if (!argv)
		return (-1);

	ex_val = exec(argv, name, *hist);
	(*hist)++;
	for (idx = 0; argv[idx]; idx++)
		free(argv[idx]);
	free(argv);
	argv = NULL;
	return (ex_val);
}

char **_get_args(char **argv)
{
	size_t read, n;
	char *line_ptr;
       
	n = 0;
	line_ptr= NULL;
	read = getline(&line_ptr, &n, stdin);
	if (read == 1 || read == -1)
	{
		if (read == -1)
		{
			perror("token failed\n");
		}
		free(line_ptr);
		return (NULL);
	}
	argv = handle_split(line_ptr, " ");
	free(line_ptr);
	return (argv);
}
