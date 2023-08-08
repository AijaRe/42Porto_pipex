#include <stdio.h>
#include <unistd.h> //access

int main(void)
{
	int fd;

	fd = access("short_poem", F_OK);
	if (fd == -1)
	{
		perror("Error with access");
		return (1);
	}
	else
		printf("No problem, the file exists.\n");
	fd = access("short_poem", W_OK | X_OK);
	if (fd == -1)
	{
		perror("Error with access");
		return (1);
	}
	else
		printf("No problem, can write to file.\n");
	return (0);chmod +
}
/*
* int access(const char *pathname, int mode)
* access command checks whether the calling program 
* has access to a specified file
* F_OK - check existance of file
* R_OK - check read permission
* W_OK - check write permission
* X_OK - check execute permission
* If access() cannot access the file, 
* it will return -1 or else it will be 0.
* To combine multiple modes, use biwise OR '|' to create bitmask.
*/