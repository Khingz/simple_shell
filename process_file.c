#include "shell.h"

/**
 * proc_file_commands - Takes a file and attempts to run the commands
 */
int process_file_cmd(char *file_path)
{
	ssize_t file;
	ssize_t read_b;
	unsigned int line_size, size_old;
	char buff[120];
	char *line;

	line_size = 0;
	size_old = 120;

	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		perror("Error ");
		return (127);
	}

	line = malloc(sizeof(char) * size_old);
	if (!line)
		return (-1);
	line[0] = '\0';

	do {
		read_b = read(file, buff, 120);
		line_size += read_b;
		line = _realloc(line, size_old, line_size);
		_strcat(line, buff);
		size_old = line_size;
	} while (read_b == 120);

	exit(0);
}
