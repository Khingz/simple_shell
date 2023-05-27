#include "shell.h"

int open_err(char *file_path);

/**
 * proc_file_commands - Takes a file and attempts to run the commands
 */
int process_file_cmd(char *file_path, int *exe_ex_val)
{
	ssize_t file;
	ssize_t read_b;
	unsigned int line_size, size_old;
	char buff[120];
	char *line;
	int ex_val, i;
	char **argv, **prox;

	line_size = 0;
	size_old = 120;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ex_val = open_err(file_path);
		return (*exe_ex_val);
	}

	line = malloc(sizeof(char) * size_old);
	if (!line)
		return (-1);
	line[0] = '\0';

	do {
		read_b = read(file, buff, 119);
		if (read_b == 0 && line_size == 0)
			return (*exe_ex_val);
		buff[read_b] = '\0';
		line_size += read_b;
		line = _realloc(line, size_old, line_size);
		_strcat(line, buff);
		size_old = line_size;
	} while (read_b == 120);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	_replace_var(&line, exe_ex_val);
	_handle_line(&line, line_size);
	argv = handle_split(line, " ");
	free(line);
	if (!argv)
		return (0);
	if (_check_args(argv) != 0)
	{
		*exe_ex_val = 2;
		free_args(argv, argv);
		return (*exe_ex_val);
	}
	prox = argv;

	for (i = 0; argv[i]; i++)
	{
		if (_strncmp(argv[i], ";", 1) == 0)
		{
			free(argv[i]);
			argv[i] = NULL;
			ex_val = _call_args(argv, prox, exe_ex_val);
			argv = &argv[++i];
			i = 0;
		}
	}

	ex_val = _call_args(argv, prox, exe_ex_val);

	free(prox);
	return (ex_val);
}

int open_err(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

