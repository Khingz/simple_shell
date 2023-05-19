#include "shell.h"

/**
 * sig_handler - handles new prompt upon a signal.
 * @signal: signal.
 */
void handle_signal(int sig)
{
	char *prompt = "\n$ ";
	(void)sig;

	signal(SIGINT, handle_signal);
	write(STDIN_FILENO, prompt, 3);
}
