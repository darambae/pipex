/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:28:29 by dabae             #+#    #+#             */
/*   Updated: 2024/03/01 14:30:44 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**whole_paths(char **envp)
{
	int		j;
	char	*whole_path;
	char	**path_arr;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp("PATH=", envp[j], 5) == 0)
		{
			whole_path = ft_strdup(envp[j] + 5);
			path_arr = ft_split(whole_path, ':');
		}
		j++;
	}
	if (!whole_path || !path_arr)
		return (NULL);
	return (path_arr);
}

char	*get_cmd_path(char *cmd_name, char **envp)
{
	int		j;
	char	*cmd_path;
	char	**path_arr;

	path_arr = whole_paths(envp);
	j = 0;
	while (path_arr[j])
	{
		cmd_path = ft_strjoin(path_arr[j], "/");
		cmd_path = ft_strjoin(cmd_name, cmd_name);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
		{
			ft_free_tab(path_arr);
			return (cmd_path);
		}
		j++;
	}
	free(cmd_path);
	ft_free_tab(path_arr);
	perror("Command not exist or unexecutable");
	return (NULL);
}

char	**free_triple_arr(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_free_tab(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	***trim_cmds(int ac, char **av)
{
	int		i;
	char	***cmds;

	/*getting command lines*/
	cmds = malloc(sizeof(char **) * (ac - 2));
	if (!cmds)
	{
		free(cmds);
		return (NULL);
	}
	i = 2;
	while (i < ac - 1)
	{
		cmds[i - 2] = ft_split(av[i], ' ');
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
