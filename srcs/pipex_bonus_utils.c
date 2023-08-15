/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:31:42 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/15 12:04:33 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

void	free_tab_and_exit(char **strs, char *message)
{
	ft_free_tab(strs);
	ft_error(message, 1);
}

void	check_input(int argc)
{
	if (argc < 5)
	{
		ft_printf("Invalid input.\nValid input:\n");
		ft_printf("  ./pipex infile cmd1 cmd2 cmdx ... outfile.\n");
		ft_printf("  ./pipex here_doc LIMITER cmdx ... outfile\n");
		return ;
	}
}

void	check_file_access(char *filename, int flag)
{
	if (flag == 0)
	{
		if (access(filename, F_OK) == -1)
			ft_error("Infile access error", 1);
		else if (access(filename, R_OK) == -1)
			ft_error("Infile access error", 1);
	}
	if (flag == 1)
	{
		if (access(filename, W_OK | R_OK) == -1)
			ft_error("Outfile access error", 1);
	}
}
