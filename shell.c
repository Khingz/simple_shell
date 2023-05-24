#include "shell.h"

/**
 * main - program that run a simple UNIX command for an interpreter.
 * @argc: arguement count.
 * @argv: arguement vector.
 * Return: 0.
 */
int main(int argc, char *argv[])
{
	char *prmpt;
	int ex_val = 0, ex_val_n;
	int *exe_ex_val;

	signal(SIGINT, handle_signal);
	exe_ex_val = &ex_val_n;
	hist = 1;
	prmpt = "$ ";
	name = *argv;
	aliases = NULL;
	*exe_ex_val = 0;
	environ = _copy_env();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		ex_val = process_file_cmd(argv[1]);
		free_env();
		return (ex_val);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ex_val != END_OF_FILE && ex_val != EXIT)
			ex_val = _handle_args(exe_ex_val);
		free_env();
		free_aliase_list(aliases);
		return (*exe_ex_val);
	}
	while (1)
	{
		write(STDOUT_FILENO, prmpt, 2);
		ex_val = _handle_args(exe_ex_val);
		if (ex_val == END_OF_FILE || ex_val == EXIT)
		{
			if (ex_val == END_OF_FILE)
				write(STDOUT_FILENO, "\n", 1);
			free_env();
			free_aliase_list(aliases);
			exit(*exe_ex_val);
		}
	}
	free_env();
	free_aliase_list(aliases);
	return (*exe_ex_val);
}
