#include "shell.h"

int exec(char **argv, char *name, int hist)
{
	pid_t pid_child;
	int status, flag, ex_val;
	char *cmd;
       
	cmd = *argv;
	flag = ex_val = 0;
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
		{
			if (errno == EACCES)
				ex_val = create_err(name, hist, argv, 126);
			else
				ex_val = create_err(name, hist, argv, 127);
			free_env();
			free_args(argv);
			_exit(ex_val);
		}
		/*if (access(cmd, X_OK) == -1)
			return (create_err(name, hist, *arg, 126));*/
		execve(cmd, argv, NULL);
		if (errno == EACCES)
			ex_val = create_err(name, hist, argv, 126);
		free_env();
		free_args(argv);
		_exit(ex_val);
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


/**
 * handle_args - get cmd and calls the execution of a command.
 */
int handle_args(char *name, int *hist, exe_ex_val)
{
	int ex_val;
	size_t idx;
	ssize_t read;
	char **args, *line_ptr;
	int (*builtin)(char **argv);

	line_ptr = NULL;
	idx = 0;
	read = getline(&line_ptr, &idx, stdin);
	if (read == -1)
	{
		free(line_ptr);
		return (-2);
	}
	if (read == 1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		free(line_ptr);
		return (handle_args(name, hist, exe_ex_val));
	}
	line_ptr[read - 1] = '\0';
i	replace_variable(args, exe_ex_val);
	args = handle_split(line_ptr, " ");
	free(line_ptr);
	if (!args)
		return (0);
	builtin = _getbuiltin(args[0]);
	if (builtin)
	{
		ex_val = builtin(args + 1);
		if (ret != -3)
		{
			*exe_ex_val = ex_val;
			if (ex_val != -3 && ex_val != 0)
				create_err(name, *hist, args, ex_val);
		}
	}
	else
	{
		exe_ex_val = exec(args, name, *hist);
		ex_val = *exe_ex_val;

	(*hist)++;
	free_args(args);
	return (ex_val);
}


/**char **clear_input(char **argv)
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
	int (*builtin)(char **argv);

	argv = _get_args(argv);
	if (!argv)
	{
		return (-1);
	}
	builtin = get_builtin(argv[0]);
	if (builtin)
	{
		ex_val = builtin(argv);
		if(ex_val)
			create_err(name, *hist, argv, ex_val);
	}
	else
		ex_val = exec(argv, name, *hist);
	(*hist)++;
	for (idx = 0; argv[idx]; idx++)
		free(argv[idx]);
	free(argv);
	return (ex_val);
}

int _get_args(char **argv)
{
	size_t read, n;
	char *line_ptr, **args;
	int idx;
       
	n = 0;
	line_ptr= NULL;
	read = getline(&line_ptr, &n, stdin);
	if (read == 1 || read == -1)
	{
		free(line_ptr);
	}
	if (read == 1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		return (_get_args(argv));
	}
	if (read == -1)
	{
		return (-2);
	}
	args = handle_split(line_ptr, " ");
	if (!args)
	{
		perror("Failed to tokenize");
		return (-1);
	}

	for (idx = 0; args[idx]; idx++)
		argv[idx] = args[idx];
	free(line_ptr);
	free(args);
	return (0);
}
*/
