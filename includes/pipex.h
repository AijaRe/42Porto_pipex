/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:32:35 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/17 12:14:13 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

/* pipex.c */
int		main(int argc, char **argv, char **env);
/* pipex_path.c */
char	**create_path_array(char **env);
char	*find_path(char *cmd, char **path);
/* pipex_utils.c */
int		check_input(int argc);
void	free_tab_and_exit(char **strs, char *message);
void	ft_error(char *str, int exit_code);

#endif
