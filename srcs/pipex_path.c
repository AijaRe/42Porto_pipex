/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:31:23 by arepsa            #+#    #+#             */
/*   Updated: 2023/08/15 12:01:32 by arepsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		ft_error("Couldn't find path", 1);
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
			return (full_path);
		free(full_path);
		i++;
	}
	return (0);
}
