#include "pipex_bonus.h"

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_tab_and_exit(char **strs, char *message)
{
		ft_free_tab(strs);
		ft_error(message);
}

void	check_input(int argc)
{
	if (argc < 5)
	{
		ft_printf("Invalid input.\nValid input:\n\
				./pipex infile cmd1 cmd2 cmdx ... outfile.\n\
				./pipex here_doc LIMITER cmdx ... outfile\n");
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

void	open_file(char *infile)
{
	int fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		ft_error("Infile error");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	open_here_doc(char *here_doc)
{
	int	fd;
	
	fd = open(here_doc, O_RDONLY);
	if (fd == -1)
	{
		unlink(here_doc);
		ft_error("Here_doc error");
	}
	dup2(fd, STDIN_FILENO);
	unlink(here_doc);
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
		path_array[i] = temp;
		i++;
	}
	return (path_array);
}

char	*find_path(char *cmd, char **path)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], cmd);
		if (!full_path)
			free_tab_and_exit(path, "Path not found");
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
	if (!final_path)
	{
		ft_free_tab(cmds);
		ft_free_tab(path);
		free(final_path);
		ft_error("Path error");
	}
	if (execve(final_path, cmds, NULL) == -1)
	{
		ft_free_tab(cmds);
		ft_free_tab(path);
		free(final_path);
		perror("Command not found");
		exit(127);
	}
}

void	output_file(char *outfile, char *cmd, char **path)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (fd == -1)
		free_tab_and_exit(path, "Outfile error");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_execute(cmd, path);
}

void	ft_pipex(char *cmd, char **path)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		free_tab_and_exit(path, "Pipe error");
	pid = fork();
	if (pid == -1)
		free_tab_and_exit(path, "Fork error");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_execute(cmd, path);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

void	get_input(char *limiter)
{
	int	fd;
	char *line;
	
	fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd == -1)
	{
		unlink("here_doc");
		ft_error("Here_doc error");
	}
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
		if (!line)
			ft_error("GNL error");
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	open_here_doc("here_doc");
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	char **path_array;

	check_input(argc);
	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		get_input(argv[2]);
		i = 3;
	}
	else
		open_file(argv[1]);
	path_array = create_path_array(env);
	if (!path_array)
		ft_error("Path not found");
	while (i < argc - 2)
	{
		ft_pipex(argv[i++], path_array);
	}
	output_file(argv[argc - 1], argv[argc - 2], path_array);
	check_file_access(argv[1], argv[argc - 1]);
	ft_free_tab(path_array);
	return (0);
}
