#include "shell.h"

int exec(char **argv, char **begin)
{
	pid_t pid_child;
	int status, flag, ex_val;
	char *cmd;
       
	cmd = argv[0];
	flag = ex_val = 0;
	if (cmd[0] != '.' && cmd[0] != '/')
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
				ex_val = create_err(argv, 126);
			else
				ex_val = create_err(argv, 127);
			free_env();
			free_args(argv, begin);
			free_aliase_list(aliases);
			_exit(ex_val);
		}
		execve(cmd, argv, NULL);
		if (errno == EACCES)
			ex_val = create_err(argv, 126);
		free_env();
		free_args(argv, begin);
		free_aliase_list(aliases);
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
int handle_args(int *exe_ex_val)
{
	int ex_val,  idx;
	char **args, **begin;
	char *line_ptr;

	line_ptr = NULL;
	line_ptr = get_args(line_ptr, exe_ex_val);
	if (!line_ptr)
		return (END_OF_FILE);

	args = handle_split(line_ptr, " ");
	free(line_ptr);
	args = substi_aliases(args);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ex_val = 2;
		free_args(args, args);
		return (*exe_ex_val);
	}
	begin = args;
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], ";", 1) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			ex_val = call_args(args, begin, exe_ex_val);
			args = &args[++idx];
			idx = 0;
		}
	}
	ex_val = call_args(args, begin, exe_ex_val);

	free(begin);
	return (ex_val);
}

/**
 * get_args - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *line, int *exe_ex_val)
{
	size_t i = 0;
	ssize_t read;
	char *prmpt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &i, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prmpt, 2);
		return (get_args(line, exe_ex_val));
	}

	line[read - 1] = '\0';
	replace_var(&line, exe_ex_val);
	handle_line(&line, read);
	return (line);
}

/**
 * call_args - Partitions operators from commands and calls
 */
int call_args(char **args, char **begin, int *exe_ex_val)
{
	int idx, ex_val;

	if (!args[0])
		return (*exe_ex_val);
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], "||", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			ex_val = run_args(args, begin, exe_ex_val);
			if (*exe_ex_val != 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ex_val);
			}
		}
		else if (_strncmp(args[idx], "&&", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			ex_val = run_args(args, begin, exe_ex_val);
			if (*exe_ex_val == 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ex_val);
			}
		}
	}

	ex_val = run_args(args, begin, exe_ex_val);
	return (ex_val);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'
 */
int check_args(char **args)
{
	size_t i;
	char *curr, *next;

	for (i = 0; args[i]; i++)
	{
		curr = args[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (create_err(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_err(&args[i + 1], 2));
		}
	}
	return (0);
}
