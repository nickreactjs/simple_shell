#include "shell.h"

/**
 * p_l - process line which is received by getline
 * @line: received line
 * @env: environment variable
 * @head: head of file
 * Return: 0 on succes, -1 if fails
 */
int p_l(char *line, char **env, list_t **head, char **av)
{
	char *command[4] = {"", "", "", ""};
	int len = 0, status, i = 0, j = 1;
	pid_t child_pid = 0;
	char buffer[100];
	char *lcommand = &buffer[0];

	command[1] = NULL;
	command[2] = NULL;
	command[3] = NULL;
	if (!_strcmp(line, "exit\n"))
	{
		return (-1);
	}
	if (!_strcmp(line, "\n"))
		return (0);
	len = _strlen(line);
	line[len - 1] = '\0';
	if (!_strcmp(line, "env"))
	{
		for (; env[i + 1]; i++)
			printf("%s\n", env[i]);
	} else
	{
		command[0] = strtok(line, " ");
		command[0] = checkpath(*head, command[0], lcommand);
		while ((command[j] = strtok(NULL, "")))
			j++;
		child_pid = fork();
		if (child_pid == -1)
			return (-1);
		else if (child_pid == 0)
		{
			if (execve(command[0], command, NULL) == -1)
				perror(av[0]);
			return (-1);
		}
			wait(&status);
	}
	return (0);
}
