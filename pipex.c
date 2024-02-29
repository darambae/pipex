/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:57 by dabae             #+#    #+#             */
/*   Updated: 2024/02/28 20:27:44 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static int	check_av(char **arr)
// {
// 	perror("Arguments error");
// 	//free char double arr
// 	return (EXIT_FAILURE);
// }

static void	init_av(int ac, char **av, t_pipe *args, char **envp)
{
	char	**args_arr;
	int		i;

	args_arr = malloc(sizeof(char *) * ac);
	if (!args_arr)
		exit(2);
	i = 0;
	while (i < ac - 1)
	{
		args_arr[i] = ft_split(av[i + 2], " ");
		i++;
	}
	args_arr[i] = NULL;
	if (ac < 5)
	{
		if (args_arr)
			free(args_arr);
		perror("Arguments initializing error");
		exit(2);
	}
	if (ft_strcmp("here_doc", args_arr[1]) == 0)
		args->here_doc = true;
	args->here_doc = false;
	args->num_cmd = ac - 3;
	args->cmd_args = args_arr;
	free(args_arr);
}

// static void	pipex	(int in_fd, int out_fd, t_pipe *args)
// {
	
// }

int	main(int ac, char **av, char **envp)
{
	t_pipe	*args;
	int		infile;
	int		outfile;

	if (ac < 5)
		return (EXIT_FAILURE);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT, 0777);

	if (infile < 0 || outfile < 0)
		return (EXIT_FAILURE);
	args->in_fd = infile;
	args->out_fd = outfile;
	printf("%s\n", envp[1]);
	init_av(ac, av, args, envp);
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