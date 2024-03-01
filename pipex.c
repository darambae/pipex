/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:57 by dabae             #+#    #+#             */
/*   Updated: 2024/02/29 19:30:41 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"

static void	child_process(int *end, t_pipe *args, char **av)
{
	close(end[0]);
	args->in_fd = open(args->infile, O_RDONLY);
	if (args->in_fd < 0)
		return (EXIT_FAILURE);
	;
	if (dup2(args->in_fd, STDIN_FILENO) < 0)
		perrpr("dup2 error in child process");
	close(args->in_fd);
	execve(get_cmd_path(args->cmd_args[0][0]), av[2], ?);
}

static void parent_process(int *end, t_pipe *args, char **av)
{
	close(end[1]);
	args->out_fd = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777); //O_APPEND for bonus
	if (args->out_fd < 0)
		return (EXIT_FAILURE);
	if (dup2(args->out_fd, STDOUT_FILENO) < 0 || dup2(end[0], STDIN_FILENO) < 0)
		perror("dup2 error in parent process");
	close(args->out_fd);
	execve(get_cmd_path(args->cmd_args[0][1]), av[3], ?);
}

static void	pipex(char **av, t_pipe *args, char **envp)
{
	int	end[2];
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
		child_process(end, args, av);
		
	}
	else
	{
		//parent process
		parent_process(end, args, av);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	*args;

	ft_memset(args, 0, sizeof(t_pipe));
	//check if the num of arguments is more than 5 and files exist or readable or writable
	if (ac >= 5 && !access(av[1], R_OK) && !access(av[ac - 1], W_OK))
	{
		/*getting file path*/
		args->infile = ft_strdup(av[1]);
		args->outfile = ft_strdup(av[ac - 1]);
		init_av(ac, av, args);
		pipex(av, args, envp);
	}
	else
		perror("files error or not enough input given");
	free(args);
	return (0);
}