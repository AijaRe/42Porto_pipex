#include "pipex.h"

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	check_input(int argc)
{
	if (argc < 5)
	{
		printf("Invalid input.\nValid input: \
				./pipex infile cmd1 cmd2 cmdn ... outfile.\n");
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

char	*find_path(char *cmd, char **path)
{
	char	*full_path;
	int		i;
	int		exec_error;

	i = 0;
	exec_error = -1;
	full_path = NULL;
	while (path[i] && exec_error == -1)
	{
		full_path = ft_strjoin(path[i], cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return(full_path);
		free(full_path);
		i++;
	}
	return (0);

}

void	ft_execute(char *cmd, char **path)
{
	char **cmds;
	char *final_path;
	int i;

	cmds = ft_split(cmd, ' ');
	final_path = find_path(cmds[0], path);
	i = 0;
	if (!path)
	{
		while (cmds[i])
		{
			free(cmds[i]);
			i++;
		}
		free(cmds);
		ft_error("Path error");
	}
	if (execve(final_path, cmds, NULL) == -1)
		perror("Execve error");
}

void	ft_pipex(char *cmd, char **path)
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
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_execute(cmd, path);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	char **path;
	int	i;

	check_input(argc);
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (fd[0] == -1)
		ft_error("Infile error");
	if (fd[1] == -1)
		ft_error("Outfile error");
	path = create_path_array(env);
	if (path == NULL)
		ft_error("Path not found");
	check_file_access(argv[1], argv[argc - 1]);
	i = 2;
	dup2(fd[0], STDIN_FILENO);
	while (i < argc - 2)
		ft_pipex(argv[i++], path);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_execute(argv[argc - 2], path);
	ft_free_tab(path);
	return (0);
}