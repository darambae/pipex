/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:48:50 by dabae             #+#    #+#             */
/*   Updated: 2024/03/11 16:30:55 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Handling only more than commands or here_doc */

int	main(int ac, char **av, char **envp)
{
	char	***args_cmds;

	if (ac > 5)
	{
		args_cmds = NULL;
		if (ft_strcmp(av[1], "here_doc") == 0)
			args_cmds = trim_cmds(ac - 1, av + 1);
		else
			args_cmds = trim_cmds(ac, av);
		if (!args_cmds)
		{
			free_triple_arr(args_cmds);
			exit(1);
		}
		pipex_bonus(ac, av, args_cmds, envp);
		free_triple_arr(args_cmds);
	}
	else
		err_msg_exit("Not enough arguments");
	return (EXIT_SUCCESS);
}
