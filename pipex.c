/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:57 by dabae             #+#    #+#             */
/*   Updated: 2024/03/08 10:36:20 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	child_process(int *end, char **av)
{
	int	in_fd;

	close(end[0]);
	in_fd = open(av[1], O_RDONLY);
	if (in_fd < 0 || access(av[1], R_OK) == -1)
		return (EXIT_FAILURE);
	if (dup2(in_fd, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)
	{
		perror("dup2 error in child process");
		return (EXIT_FAILURE);
	}
	close(in_fd);
	close(end[1]);
	return (EXIT_SUCCESS);
}

static int	parent_process(int *end, int ac, char **av)
{
	int	out_fd;

	close(end[1]);
	out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0 || access(av[ac - 1], W_OK) == -1)
		return (EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) < 0 || dup2(end[0], STDIN_FILENO) < 0)
		error_handler();
	close(out_fd);
	close(end[0]);
	return (EXIT_SUCCESS);
}

static int	pipex(int ac, char **av, char ***cmds, char **envp)
{
	int		end[2];
	pid_t	pid1;
	char	*cmd_path;

	cmd_path = NULL;
	if (pipe(end) == -1)
		error_handler();
	pid1 = fork();
	if (pid1 < 0)
		error_handler();
	else if (pid1 == 0)
	{
		child_process(end, av);
		cmd_path = get_cmd_path(cmds[0][0], envp);
		if (!cmd_path || execve(cmd_path, cmds[0], envp) == -1)
			error_handler();
		free(cmd_path);
	}
	parent_process(end, ac, av);
	cmd_path = get_cmd_path(cmds[1][0], envp);
	if (!cmd_path || execve(cmd_path, cmds[1], envp) == -1)
		error_handler();
	free(cmd_path);
	return (EXIT_SUCCESS);
}

void	free_triple_arr(char ***arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		ft_free_tab(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

int	main(int ac, char **av, char **envp)
{
	char	***args_cmds;

	if (ac > 4)
	{
		args_cmds = NULL;
		if (ft_strcmp(av[1], "here_doc") == 0)
			args_cmds = trim_cmds(ac - 1, av + 1);
		else
			args_cmds = trim_cmds(ac, av);
		if (!args_cmds)
		{
			free_triple_arr(args_cmds);
			return (EXIT_FAILURE);
		}
		if (ac == 5)
			pipex(ac, av, args_cmds, envp);
		else if (ac > 5 || ft_strcmp(av[1], "here_doc") == 0)
			pipex_bonus(ac, av, args_cmds, envp);
		free_triple_arr(args_cmds);
	}
	else
		error_handler();
	return (EXIT_SUCCESS);
}
