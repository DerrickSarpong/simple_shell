#ifndef MAIN_H
#define MAIN_H

typedef struct
{
	char *line;
	char **args;
} shell_t;

void free_shell_data(shell_t *shell_data);

extern char **environ;

void print_environ(void);

void free_string_array(char *args[]);

int _execute_command(char *args[]);

void _print_error(char *sn, char *command);

int _strlen(char *s);

int _strcmp(char *s1, char *s2);

char **tokenize_string(char *s, const char *t);

void remove_newline(char *s);

#endif /* MAIN_H */
