#include <unistd.h>
#include <fcntl.h> //open
#include <stdio.h> //perror
#include <string.h> //strerror
#include <stdlib.h> //exit, free, malloc
#include <errno.h> //errno

int main(int argc, char **argv)
{
	int fd;
	int	bytes_read;
	char *buff;

	if (argc != 2)
	{
		perror("wrong usage, one argument required\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	buff = malloc(sizeof(char) * 100);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	bytes_read = read(fd, buff, 10);
	printf("called read(%d, buff, 10). Returned that %d bytes were read.\n", fd, bytes_read);
	buff[bytes_read] = '\0';
	printf("Those bytes are: %s\n", buff);
	close(fd);
	free(buff);
	return(0);
}
