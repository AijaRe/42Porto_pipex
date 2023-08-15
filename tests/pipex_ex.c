#include "pipex.h"

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

void	check_file_access(char *infile, char *outfile)
{
	if (access(infile, F_OK) == -1)
		ft_error("Infile access error");
	else if (access(infile, R_OK) == -1)
		ft_error("Infile access error");
	if (access(outfile, W_OK | R_OK) == -1)
		ft_error("Outfile access error");
}

char	**create_path_array(char **env)
{
	int		i;
	char	*temp;
	char	**path_array;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i] && path == NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (path == NULL)
		ft_error("Couldn't find path.");
	path_array = ft_split(path + 5, ':');
	i = 0;
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		free(path_array[i]);
		path_array[i] =  temp;
		i++;
	}
	return (path_array);
}

char	*find_path(char **path, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return(full_path);
		free(full_path);
		i++;
	}
	return (0);
}

void	in_process(int fd, char *cmd1, char **path, int *pipefd)
{
	char **cmds;
	char *full_path;

	cmds = ft_split(cmd1, ' ');
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[0]);
	if (access(cmds[0], F_OK | X_OK) != -1)
	{
		if (execve(cmds[0], cmds, NULL) == -1)
		{
			perror("Command not found");
			ft_free_tab(cmds);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		full_path = find_path(path, cmds[0]);
		if (!full_path)
		{
			perror("Command not found");
			ft_free_tab(cmds);
			exit(127);
		}
		if (execve(full_path, cmds, NULL) == -1)
		{
			perror("Command not found");
			ft_free_tab(cmds);
			exit(EXIT_FAILURE);
		}
	}
	ft_free_tab(cmds);
	exit(EXIT_FAILURE);
}

void	out_process(int fd, char *cmd2, char **path, int *pipefd)
{
	char **cmds;
	char *full_path;

	cmds = ft_split(cmd2, ' ');
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd);
	close(pipefd[1]);
	if (access(cmds[0], F_OK | X_OK) != -1)
	{
		if (execve(cmds[0], cmds, NULL) == -1)
		{
			perror("Command not found");
			ft_free_tab(cmds);
			exit(EXIT_FAILURE);
		}
	}
	else 
	{
		full_path = find_path(path, cmds[0]);
		if (!full_path)
		{
			perror("Command not found");
			ft_free_tab(cmds);
			exit(127);
		}
		if (execve(full_path, cmds, NULL) == -1)
		{
			perror("Command not found");
			ft_free_tab(cmds);
			exit(EXIT_FAILURE);
		}
	}
	ft_free_tab(cmds);
	exit(EXIT_FAILURE);
}

void	ft_pipex(int *fd, char *cmd1, char *cmd2, char **path)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		ft_error("Pipe error");
	pid = fork();
	if (pid == -1)
		ft_error("Fork error");
	if (pid == 0)
	{
		in_process(fd[0], cmd1, path, pipefd);
	}
	else
	{
		wait(NULL);
		out_process(fd[1], cmd2, path, pipefd);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	char **path;

	check_input(argc);
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (fd[0] == -1)
		ft_error("Infile error");
	if (fd[1] == -1)
		ft_error("Outfile error");
	path = create_path_array(env);
	if (path == NULL)
		ft_error("Path not found");
	check_file_access(argv[1], argv[4]);
	ft_pipex(fd, argv[2], argv[3], path);
	ft_free_tab(path);
	return (0);
}