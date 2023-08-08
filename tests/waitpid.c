#include <stdio.h>
#include <sys/wait.h> //wait
#include <unistd.h> //fork

int main(void)
{
	int pid1;
	int pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Fork error");
		return (1);
	}
	if (pid1 == 0)
	{
		sleep(4);
		printf("%d (child1) finished execution\n", getpid());
		return (0);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Fork error");
		return (2);
	}
	if (pid2 == 0)
	{
		sleep(1);
		printf("%d (child2) finished execution\n", getpid());
		return (0);
	}
	int pid1_result = waitpid(pid2, NULL, 0);
	printf("Waited for child 2: %d\n", pid1_result);
	int pid2_result = waitpid(pid1, NULL, 0);
	printf("Waited for child 1: %d\n", pid2_result);
	return (0);
}
/*
* waitpid arguments:
* - pid_t process id
* - int *status (the same as for wait())
* - int options
* Status *int will be filled with the exit status.
* If status is not NULL, wait() and waitpid() store status information
* in the int to which it points.
* Commonly used option flag W_NOHANG - makes waitpid tell
* whether the process has finished (and if so what its exit status was) rather than wait for it to finish.
* If successful, waitpid() returns a value of the process 
* (usually a child) whose status information has been obtained.
*/