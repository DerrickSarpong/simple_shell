#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * print_environ - prints shell environment
 *
 * Return: void
 */
void print_environ(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
}
