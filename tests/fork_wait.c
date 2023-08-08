#include <stdio.h>
#include <unistd.h> //fork
#include <stdlib.h> //exit
#include <sys/wait.h> //wait

int main(void)
{
	int id;

	id = fork();
	printf("Test the fork..should appear 2x, from %d.\n", id);
	if (id == 0)
	{
		printf("Hello from child process.\n");
	}
	if (id != 0)
	{
		wait(NULL);
		id = fork();
		printf("2nd fork from main:%d\n", id);
	}
	
	return(0);
}

/*
./a.out   
* Test the fork..should appear 2x, from 104113.
* Test the fork..should appear 2x, from 0. == id from the child process
* wait() blocks the calling process until one of its 
* child processes exits or a signal is received. 
* wait arguments: int *status.
* NULL = do not take status into account.
* After child process terminates, parent continues its execution.
* If more than one child processes are terminated than wait() reap 
* any arbitrarily child and return a PID of that child process.
*/