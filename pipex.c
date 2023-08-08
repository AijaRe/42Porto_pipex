#include <stdio.h> //perror
#include <unistd.h> //access
#include <stdlib.h> //exit, free, malloc
#include <fcntl.h> //open
#include <sys/wait.h> //wait

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	check_input(int argc)
{
	if (argc != 5)
	{
		printf("Invalid input.\nValid input: \
				./pipex infile cmd1 cmd2 outfile.\n");
		return ;
	}
}

void	check_access(char *infile, char *outfile)
{
	if (access(infile, F_OK) == -1)
		perror("Infile access error:");
	else if (access(infile, R_OK) == -1)
		perror("Infile access error:");
	if (access(outfile, W_OK | R_OK) == -1)
		perror("Outfile access error:");
}

void	ft_pipex(/*int *fd, char *cmd1, char *cmd2, char *path*/)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("Hello from child process.\n");
		in_process(fd[0], cmd1, path, pipefd);
	}
	else
	{
		wait(NULL);
		printf("Hello from main process.\n");
		//out_process(fd[1], cmd2, path, pipefd);

	}


}

int	main(int argc, char **argv)
{
	int	fd[2];
	char path[] = "/usr/bin/ls";

	check_input(argc);
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	check_access(argv[1], argv[4]);
	ft_pipex(fd, argv[2], argv[3], path);
	close(fd[0]);
	close(fd[1]);
	return (0);
}