#include "shell.h"


/**
 * pathfinder - a Nissan 4x4 truck, joking it looks for the path
 * @input: the command to be looked for
 * Return: full path
 */
char *pathfinder(char *input)
{
	char *path_env = _getenv("PATH");
	char *path_copy = _strdup(path_env);
	char *path_dir = NULL, *full = NULL;
	char *full_path = malloc(PATH_MAX);

	if (access(input, X_OK) == 0)
	{
		return (input);
	}
	if (full_path == NULL)
	{
		perror("malloc fullpath error");
		exit(EXIT_FAILURE);
	}
	if (path_copy == NULL)
	{
		perror("strdup error");
		exit(EXIT_FAILURE);
	}
		path_dir = strtok(path_copy, ":");
	while (path_dir)
	{
		full_path[0] = '\0';
		_strcpy(full_path, path_dir);
		_strcat(full_path, "/");
		_strcat(full_path, input);
		if (access(full_path, F_OK) == 0)
		{
			full = _strdup(full_path);
			free(path_copy);
			free(full_path);
			return (full);
		}
		path_dir = strtok(NULL, ":");
	}
free(full_path);
free(path_copy);
return (NULL);
}
/**
 * main - main program
 * Return: 1 0
 */
int main(void)
{
char *tknptr, *argv[5], *full_path = NULL, *input = NULL;
size_t n = 0;
ssize_t gtln;
int i = 0, status = 0;
pid_t child;

while (1)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
	}
	gtln = getline(&input, &n, stdin);
	if (_strcmp(input, "env\n") == 0)
	{
		print_env();
		continue;
	}
	if (gtln > 0 && input[gtln - 1] == '\n')
	{
	input[gtln - 1] = '\0';
	}
	i = 0;
	tknptr = strtok(input, " ");
	while (tknptr != NULL)
	{
		argv[i] = tknptr;
		tknptr = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;
	if (gtln == -1 || _strcmp(argv[0], "exit") == 0)
	{
	argv[0] = NULL;
	break;
	}
	if (argv[0] == NULL || _strcmp(argv[0], "\t") == 0)
	{
	continue;
	}
	full_path = pathfinder(argv[0]);
	if (full_path != NULL)
	{
		argv[0] = _strdup(full_path);
		full_path = NULL;
	}
	else
	{
		perror(argv[0]);
		continue;
	}
	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	if (child == 0)
	{
		execute(argv);
		exit(0);
	}
	else
	{
		waitpid(child, &status, WUNTRACED);
	}
free(argv[0]);
}
free(input);
return (EXIT_SUCCESS);
}
/**
 * execute - executes the argv from main
 * @exe: the executable command
 */
void execute(char **exe)
{
	if (execve(exe[0], exe, environ) == -1)
	{
		exit(EXIT_FAILURE);
	}
}


