/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:57 by dabae             #+#    #+#             */
/*   Updated: 2024/03/01 18:33:10 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	child_process(int *end, char **av)
{
	int in_fd;

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
	int out_fd;

	close(end[1]);
	out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); //O_APPEND for bonus
	if (out_fd < 0 || access(av[ac - 1], W_OK) == -1)
		return (EXIT_FAILURE);
	if (dup2(out_fd, STDOUT_FILENO) < 0 || dup2(end[0], STDIN_FILENO) < 0)
	{
		perror("dup2 error in parent process");
		return (EXIT_FAILURE);
	}
	close(out_fd);
	close(end[0]);
	return (EXIT_SUCCESS);
}

static void	pipex(int ac, char **av, char ***cmds, char **envp)
{
	int		end[2];
	pid_t	pid1;

	if (pipe(end) == -1)
		perror("pipe error");
	//end[0] = read end, end[1] = write end
	pid1 = fork();
	if (pid1 < 0)
		perror("Fork error");
	else if (pid1 == 0)	
	{
		//child process
		child_process(end, av);
		printf("%s\n", cmds[0][0]);
		if (!get_cmd_path(cmds[0][0], envp) ||
			execve(get_cmd_path(cmds[0][0], envp), cmds[0], envp) == -1)
			perror("execve error");
	}
	//parent process
	parent_process(end, ac, av);
	if (!get_cmd_path(cmds[1][0], envp) ||
		execve(get_cmd_path(cmds[1][0], envp), cmds[1], envp) == -1)
		perror("execve error");
}

int	main(int ac, char **av, char **envp)
{
	char	***args_cmds;

	args_cmds = NULL;
	// check if the num of arguments is more than 5 and files exist or readable or writable
	if (ac >= 5)
	{
		/*getting file path*/
		args_cmds = trim_cmds(ac, av);
		if (!args_cmds)
		{
			free_triple_arr(args_cmds);
			return (EXIT_FAILURE);
		}
		pipex(ac, av, args_cmds, envp);
	}
	else
	{
		perror("files error or not enough input given");
		return (EXIT_FAILURE);
	}
	free_triple_arr(args_cmds);
	return (EXIT_SUCCESS);
}