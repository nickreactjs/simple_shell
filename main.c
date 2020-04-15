#include "shell.h"
/**
 * main - shell
 * @ac: number of arguments
 * @av: Null terminated array of strings/arguments
 * @env: NULL terminated array of environment variables
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t nread = 0;
	list_t *head = NULL;
	int printed = 0, interactive = isatty(STDIN_FILENO);

	listpath(&head, env);
	while (1)
	{
		if (interactive == 1)
			printed = write(1, "$ ", 2);
		wait(&printed);
		nread = getline(&line, &n, stdin);
		if (nread != -1)
		{
			if (p_l(line, env, &head, av) == -1)
			{
				free(line);
				line = NULL;
				goto finish;
			}
		}
		free(line);
		line = NULL;
		n = 0;
		if (nread == EOF)
		{
			_putchar('\n');
			goto finish;
		}
		if (interactive != 1)
			goto finish;
	}
	finish:
	free_list(head);
	exit(0);
	(void)ac;
}
