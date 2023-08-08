#include <unistd.h> //pipe
#include <stdio.h> //perror
#include <sys/wait.h>

int	main()
{
	int	fd[2];
	int	pid1;
	int pid2;
	char *args1[] = {"/usr/bin/ls", "-l", NULL};
	char *args2[] = {"/usr/bin/grep", "fork", NULL};

	if(pipe(fd) == -1)
	{
		perror("Pipe error");
		return (1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Fork error");
		return (2);
	}
	if (pid1 == 0)
	{
		//duplicate (redirect) write end of the pipe to stdout
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/ls", args1, NULL);
		perror("Execve error");
		return (3);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Fork error");
		return (4);
	}
	if (pid2 == 0)
	{
		//redirect read end of the pipe to stdin
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep", args2, NULL);
		perror("Execve error");
		return (5);
	}
	//close main process fds
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

/*
* cdm -> stdout -> pipe -> stdin -> cmd2
*/