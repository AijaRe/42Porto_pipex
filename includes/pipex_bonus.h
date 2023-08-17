/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:32:28 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/17 12:14:21 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
/* perror */
# include <stdio.h> 
/* access */
# include <unistd.h>
/* exit, free, malloc */
# include <stdlib.h> 
/* open */
# include <fcntl.h>
/* wait */
# include <sys/wait.h>

/* pipex_bonus.c */
int		main(int argc, char **argv, char **env);
/* pipex_bonus_path.c */
char	*find_path(char *cmd, char **path);
char	**create_path_array(char **env);
/* pipex_bonus_heredoc.c */
void	open_here_doc(char *here_doc);
void	get_input(char *limiter);
void	here_doc_error(char *here_doc);
/* pipex_bonus_utils.c */
int		check_input(int argc);
void	free_tab_and_exit(char **strs, char *message);
void	ft_error(char *str, int exit_code);

#endif
