/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:31:35 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/17 12:13:28 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static void	output_file(int argc, char **argv, char **path, char **env)
{
	int	fd;

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		fd = open(argv[argc -1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(argv[argc -1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		free_tab_and_exit(path, "Outfile error");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_execute(argv[argc - 2], path, env);
}

static void	ft_pipex(char *arg, char **path, char **env)
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
		ft_execute(arg, path, env);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**path_array;

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
		ft_error("Path not found", 1);
	while (i < argc - 2)
		ft_pipex(argv[i++], path_array, env);
	output_file(argc, argv, path_array, env);
	ft_free_tab(path_array);
	return (0);
}
