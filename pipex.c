/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:57 by dabae             #+#    #+#             */
/*   Updated: 2024/03/11 16:29:28 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* child_dup : duplicate infile to STDIN and write end to STDOUT.*/

static int	child_dup(int *end, char **av)
{
	int	in_fd;

	close(end[0]);
	in_fd = open(av[1], O_RDONLY);
	if (in_fd < 0 || access(av[1], R_OK) == -1)
	{
		close(in_fd);
		close(end[1]);
		err_msg_exit("Unable to open file");
	}
	if (dup2(in_fd, STDIN_FILENO) < 0 || dup2(end[1], STDOUT_FILENO) < 0)
	{
		close(in_fd);
		close(end[1]);
		err_msg_exit("Unable to duplicate");
	}
	close(in_fd);
	close(end[1]);
	return (EXIT_SUCCESS);
}

/* parent_dup : duplicate the output(read end) of the first command line 
to STDIN and outfile to STDOUT.*/

static int	parent_dup(int *end, int ac, char **av)
{
	int	out_fd;

	close(end[1]);
	out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0 || access(av[ac - 1], W_OK) == -1)
	{
		close(out_fd);
		close(end[0]);
		err_msg_exit("Unable to open outfile");
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0 || dup2(end[0], STDIN_FILENO) < 0)
	{
		close(out_fd);
		close(end[0]);
		err_msg_exit("Unable to duplicate");
	}
	close(out_fd);
	close(end[0]);
	return (EXIT_SUCCESS);
}

/* execute_cmd : execute the command line and then */

static int	execute_cmd(char **cmds, char **envp)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = get_cmd_path(cmds[0], envp);
	if (!cmd_path || execve(cmd_path, cmds, envp) == -1)
	{
		free(cmd_path);
		return (EXIT_FAILURE);
	}
	free(cmd_path);
	return (EXIT_SUCCESS);
}

/* by pipe() and fork(), make child & parent process and execute the two 
command lines respectively */

static int	pipex(int ac, char **av, char ***cmds, char **envp)
{
	int		end[2];
	pid_t	pid1;

	if (pipe(end) == -1)
		return (EXIT_FAILURE);
	pid1 = fork();
	if (pid1 < 0)
		return (EXIT_FAILURE);
	else if (pid1 == 0)
	{
		child_dup(end, av);
		if (execute_cmd(cmds[0], envp) == EXIT_FAILURE)
		{
			free_triple_arr(cmds);
			err_msg_exit("command not found");
		}
	}
	parent_dup(end, ac, av);
	if (execute_cmd(cmds[1], envp) == EXIT_FAILURE)
	{
		free_triple_arr(cmds);
		err_msg_exit("command not found");
	}
	exit(0);
}

/* Retrieve commands only if 4 arguments(excluding its program name) 
are given. */

int	main(int ac, char **av, char **envp)
{
	char	***args_cmds;

	if (ac == 5)
	{
		args_cmds = NULL;
		args_cmds = trim_cmds(ac, av);
		if (!args_cmds)
		{
			free_triple_arr(args_cmds);
			return (EXIT_FAILURE);
		}
		pipex(ac, av, args_cmds, envp);
		free_triple_arr(args_cmds);
		return (EXIT_SUCCESS);
	}
	else
		err_msg_exit("Invalid arguments");
}
