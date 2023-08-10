#include <stdio.h> //perror
#include <unistd.h> //access
#include <stdlib.h> //exit, free, malloc
#include <fcntl.h> //open
#include <sys/wait.h> //wait

void	in_process(int *fd, char *path)
{
	char *cmds[] = {"/usr/bin/grep", "a", NULL};

	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (access(path, X_OK) != -1)
	{
		perror("Inside 1st process access\n");
		if (execve(path, cmds, NULL) == -1)
		{
			perror("Execve error");
			exit(EXIT_FAILURE);
		}
		perror("Error...I am after execve\n");
	}
}

void	ft_pipex(int *fd, char *path)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("Hello from child process.\n");
		in_process(fd, path);
	}
	else
	{
		wait(NULL);
		printf("Hello from main process.\n");
	}
}

int	main(int argc, char **argv)
{
	int	fd[2];
	char path[] = "/usr/bin/grep";

	if (argc != 3)
	{
		perror("Wrong number of arguments.\n\
				Correct input: ./executable infile outfile.");
		return (1);
	}
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
			perror("Infile error");
			exit(EXIT_FAILURE);
	}
	fd[1] = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (fd[1] == -1)
	{
			perror("Outfile error");
			exit(EXIT_FAILURE);
	}
	ft_pipex(fd, path);
	close(fd[0]);
	close(fd[1]);
	return (0);
}