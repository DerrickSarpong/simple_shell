#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

/**
 * _print_error - prints error
 * @sn: the shell program
 * @command: the command
 *
 * Return: void
 */
void _print_error(char *sn, char *command)
{
	write(1, sn, _strlen(sn));
	write(1, ": 1: ", 5);
	write(1, command, _strlen(command));
	write(1, ": not found\n", 12);
}

/**
 * _execute_command - executes a shell command
 * @args: the arguments
 *
 * Return: int
 */
int _execute_command(char *args[])
{
	int res = 0;

	res = execve(args[0], args, environ);
	return (res);
}
/**
 * free_string_array - frees a string array from heap
 * @args: the string array
 *
 * Return: void
 */
void free_string_array(char *args[])
{
	int i = 0;

	while (args != NULL && args[i] != NULL)
	{
		free(args[i++]);
		args[i - 1] = NULL;
	}
	if (args != NULL)
	{
		free(args[i]);
		args[i] = NULL;
	}
	if (args != NULL)
	{
		free(args);
		args = NULL;
	}
}

/**
 * get_args - gets the shell arguments
 * @line: pointer to string variable for holding line
 * @args: pointer to array of strings
 *
 * Return: positive int or -1 when no line is read
 */
int get_args(char **line, char ***args)
{
	int read = 0;
	size_t len = 0;

	if (isatty(STDIN_FILENO))
		write(1, "($) ", 4);
	read = getline(line, &len, stdin);
	if (read != -1)
		*args = tokenize_string(*line, " ");
	free(*line);
	*line = NULL;
	return (read);
}


/**
 * main - simple shell main
 * @argc: the number of command line arguments
 * @argv: the command line arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	pid_t child_pid;
	int status = 0, read = 0;
	char *line = NULL, **args = NULL;

	(void) argv;
	(void) argc;
	while (1)
	{
		read = get_args(&line, &args);
		if (read == -1 || _strcmp(args[0], "exit"))
		{
			break;
		}
		else if (_strcmp(args[0], "env"))
		{
			print_environ();
		}
		else
		{
			if (access(args[0], F_OK) == -1)
			{
				/*_print_error(argv[0], args[0]);*/
			}
			else
			{
				child_pid = fork();
				if (child_pid == -1)
					return (1);
				if (child_pid == 0)
					_execute_command(args);
				else
					wait(&status);
			}
		}
		free_string_array(args);
	}
	if (read != -1)
		free_string_array(args);
	return (0);
}
