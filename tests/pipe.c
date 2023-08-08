#include <stdio.h>
#include <unistd.h> //pipe
#include <sys/wait.h>

int main(void)
{
	int fd[2];
	int id;
	int x;
	int y;

	pipe(fd);
	if (pipe(fd) == -1)
	{
		perror("Error opening pipe");
		return (1);
	}
	id = fork();
	if (id == -1)
	{
		perror ("Error with fork");
		return (4); 
	}
	if (id == 0)
	{
		close(fd[0]);
		printf("Input a number (child process): ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			perror("Error with write");
			return (2);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if(read(fd[0], &y, sizeof(int)) == -1)
		{
			perror("Error with read");
			return (3);
		}
		close(fd[0]);
		printf("Got from child process %d\n", y);
		wait(NULL);
	}
	return (0);
}
/*
* fd[0] - read end
* fd[1] - write end
 */