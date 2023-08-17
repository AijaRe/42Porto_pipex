/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:31:42 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/17 09:50:37 by arepsa           ###   ########.fr       */
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

int	check_input(int argc)
{
	if (argc < 5)
	{
		ft_printf("Invalid input.\nValid input:\n");
		ft_printf("  ./pipex infile cmd1 cmd2 cmdx ... outfile.\n");
		ft_printf("  ./pipex here_doc LIMITER cmdx ... outfile\n");
		exit(1);
	}
	return (0);
}
