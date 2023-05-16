#include "shell.h"


/**
 * main - program that run a simple UNIX command for an interpreter.
 * @argc: arguement count.
 * @argv: arguement vector.
 * Return: 0.
 */

int main(int argc, char *argv[])
{
	char *prmt;

	prmt = "$ ";

	if (argc != 1)
	{
		continue;

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}
