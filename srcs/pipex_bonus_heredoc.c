/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:31:55 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/15 12:26:32 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_here_doc(char *here_doc)
{
	int	fd;

	fd = open(here_doc, O_RDONLY);
	if (fd == -1)
	{
		unlink(here_doc);
		ft_error("Here_doc error", 1);
	}
	dup2(fd, STDIN_FILENO);
	unlink(here_doc);
}

void	get_input(char *limiter)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_CREAT | O_RDWR | O_APPEND, 0755);
	if (fd == -1)
	{
		unlink("here_doc");
		ft_error("Here_doc error", 1);
	}
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
		if (!line)
			ft_error("GNL error", 1);
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
