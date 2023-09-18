#include <stdlib.h>
#include "shell.h"
#include <stdio.h>
/**
 * free_shell_data - frees shell data from heap
 * @shell_data: pointer to shell data
 *
 * Return: void
 */
void free_shell_data(shell_t *shell_data)
{
	int i = 0;

	if (shell_data->line != NULL)
	{
		printf("Free line: %s\n", shell_data->line);
		free(shell_data->line);
	}
	if (shell_data->args != NULL)
	{
		while (shell_data->args[i] != NULL)
		{
			printf("free: %s\n", shell_data->args[i]);
			if (shell_data->args[i] != NULL)
				free(shell_data->args[i++]);
		}
		printf("free: %s\n", shell_data->args[i]);
		free(shell_data->args[i]);
		free(shell_data->args);
	}
}
