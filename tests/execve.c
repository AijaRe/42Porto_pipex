
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char cmd[] = "/usr/bin/ls";

	char *argv[] = {"ls", "-l", NULL};
	char *envp[] = {NULL};
	printf("Start of execve call %s:\n", cmd);
	printf("******************\n");
	if (execve(cmd, argv, envp) == -1)
	{
		perror("Error execve");
		return (1);
	}
	printf("Ooops...this should not appear.\n");
}

/*
* execve() is a function used to launch 
* a process from within another process. 
* The executable pointed to by "path" 
* REPLACES the current process. 
* There is no return value, because the existing process is discarded.
* Unless can't perform execve, that returns -1 in that case.
* full call is execve(path, argv, envp)
* - path to the executable which has to be launched
* - argv: array of string pointers which are passed as argument 
*   to the new program(executable). 
*   The array of pointers should be terminated by a null pointer.
* - envp: array of string pointers which are passed as 
*   environmental variables of the executable. 
*   The array of pointers should be terminated by a null pointer.
*/