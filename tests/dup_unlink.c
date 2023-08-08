#include <fcntl.h> //open
#include <unistd.h> //fork dup dup2
#include <stdio.h> //perror

int main (void)
{
	int pid;
	int fd;
	int fd2;

	pid = fork();
	if (pid == -1)
	{
		perror("Error with fork");
		return (1);
	}
	fd = 0;
	fd2 = 0;
	if (pid == 0)
	{
		fd = open("test.txt", O_WRONLY | O_CREAT, 0755);
		if (fd == -1)
		{
			perror("Error opening file");
			return (2);
		}
		fd2 = dup2(fd, 1);
		write(fd2, "Write into fd2\n", 15);
		write(fd, "Write into fd\n", 14);
		printf("I am writing to stdout from child.\n");
	}
	printf("I am writing to stdout from main.\n");
	close (fd);
	close (fd2);
}
/*
* dup creates a copy of file descriptor e.g. 3 to 4
* dup2 2nd parameter is the nb of file descriptor into which
* we want to duplicate the file (e.g. 1 for stdout and the file 
* becomes stdout)
* unlink (char *filename) will delete the file. Try instead of close.
*/