/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:57 by dabae             #+#    #+#             */
/*   Updated: 2024/02/29 09:53:49 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"

// static void	get_path(t_pipe *args, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strcmp(envp[i], "PATH") == 0)
// 		{
// 			args->paths = ft_strdup(envp[i] + 5);
// 			return ;
// 		}
// 		i++;
// 	}
// }

static void	init_av(int ac, char **av, t_pipe *args)
{
	int		i;
	char	***cmds;

	/*getting file path*/
	args->infile = ft_strdup(av[1]);
	args->outfile = ft_strdup(av[ac -1]);
	/*getting command lines*/
	cmds = malloc(sizeof(char **) * (ac - 2));
	if (!cmds)
		free(cmds);
	i = 2;
	while (i < ac - 1)
	{
		args->cmd_args[i - 2] = ft_split(av[i], ' ');
		i++;
	}
	args->cmd_args[i] = NULL;
	if (ft_strcmp("here_doc", av[1]) == 0)
		args->here_doc = true;
	args->here_doc = false;
	
}

// static void	pipex	(int in_fd, int out_fd, t_pipe *args)
// {
	
// }

int	main(int ac, char **av)
{
	t_pipe	*args;

	if (ac < 5)
		return (EXIT_FAILURE);
	ft_memset(&args, 0, sizeof(t_pipe));
	init_av(ac, av, args);
	args->paths = getenv("PATH");
	printf("%s\n", args->paths);
	// args->in_fd = open(av[1], O_RDONLY);
	// args->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT, 0777);

	// if (args->in_fd < 0 || args->out_fd < 0)
	// 	return (EXIT_FAILURE);
	//pipex(infile, outfile, args);
	
	
	// int	fd[2];
	// int	pid1 = fork();
	// int	infile;
	// int	outfile;

	// infile = open("infile", O_RDONLY, 0777);
	// outfile = open("outfile", O_WRONLY | O_CREAT, 0777);
	// if (infile == -1)
	// 	perror("Failed reading infile");
	// if (pipe(fd) == -1)
	// 	perror("Pipe Error");
	// if (pid1 < 0)
	// 	perror("Fork error");
	// if (pid1 == 0) //child process
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	execve();
	// }
	// else
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// 	execve();
	// }
	/*
	init_av()
	check_av()
	read_file()
	pipe()
	write_file()
	*/
	return (0);
}