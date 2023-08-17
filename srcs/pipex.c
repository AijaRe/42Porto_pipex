/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:30:57 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/17 12:13:41 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(char *arg, char **path, char **env)
{
	char	**cmds;
	char	*final_path;
	int		i;

	cmds = ft_split(arg, ' ');
	final_path = find_path(cmds[0], path);
	i = 0;
	if (!final_path)
	{
		ft_free_tab(cmds);
		ft_free_tab(path);
		free(final_path);
		ft_error("Path error", 127);
	}
	if (execve(final_path, cmds, env) == -1)
	{
		ft_free_tab(cmds);
		ft_free_tab(path);
		free(final_path);
		ft_error("Command not found", 127);
	}
}

static void	open_file(char *infile)
{
	int	fd;

	if (access(infile, F_OK | R_OK) == 0) 
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			ft_error("Infile error", 1);
	}
	else 
	{
		if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
			perror("Infile error");
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
			ft_error("Infile error", 1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	output_file(char *outfile, char *cmd2, char **path, char **env)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		free_tab_and_exit(path, "Outfile error");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_execute(cmd2, path, env);
}

static void	ft_pipex(char **argv, char **path, char **env)
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
		ft_execute(argv[2], path, env);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		output_file(argv[4], argv[3], path, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**path_array;

	check_input(argc);
	open_file(argv[1]);
	path_array = create_path_array(env);
	if (!path_array)
		ft_error("Path not found", 1);
	ft_pipex(argv, path_array, env);
	ft_free_tab(path_array);
	return (0);
}
