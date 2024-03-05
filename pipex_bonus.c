/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:21:08 by dabae             #+#    #+#             */
/*   Updated: 2024/03/05 14:30:32 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	here_doc_handler(char **av)
{
	char	*line;
	int		fd;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		error_handler();
	while (1)
	{
		write(1, "pipe heredoc>", 13);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strcmp(line, av[2]) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	last_process(char *outfile, char **cmds, char **envp, bool here)
{
	int	out_fd;

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!here)
		out_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0 || access(outfile, W_OK) == -1)
		return (EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		error_handler();
	close(out_fd);
	if (!get_cmd_path(cmds[0], envp) || execve(get_cmd_path(cmds[0], envp),
			cmds, envp) == -1)
		error_handler();
	return (EXIT_SUCCESS);
}

static int	pipe_fork(char **cmds, char **envp)
{
	int		end[2];
	pid_t	pid;

	pid = fork();
	if (pipe(end) == -1 || pid < 0)
		error_handler();
	if (pid == 0)
	{
		if (dup2(end[1], STDOUT_FILENO) < 0)
			error_handler();
		close(end[0]);
		close(end[1]);
		if (!get_cmd_path(cmds[0], envp) ||
			execve(get_cmd_path(cmds[0], envp), cmds, envp) == -1)
			error_handler();
	}
	if (dup2(end[0], STDIN_FILENO) < 0)
		error_handler();
	close(end[0]);
	close(end[1]);
	return (EXIT_SUCCESS);
}

int	pipex_bonus(int ac, char **av, char ***cmds, char **envp)
{
	int		i;
	int		in_fd;

	i = -1;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		i = 0;
		here_doc_handler(av);
		in_fd = open("here_doc", O_RDONLY);
	}
	else
	{
		in_fd = open(av[1], O_RDONLY);
		if (access(av[1], R_OK) == -1)
			error_handler();
	}
	if (in_fd < 0 || dup2(in_fd, STDIN_FILENO) < 0)
		return (EXIT_FAILURE);
	close(in_fd);
	while (++i < ac - 4)
	{
		if (pipe_fork(cmds[i], envp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	last_process(av[ac - 1], cmds[i], envp, ft_strcmp(av[1], "here_doc"));
	return (EXIT_SUCCESS);
}
