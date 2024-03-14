/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:48:50 by dabae             #+#    #+#             */
/*   Updated: 2024/03/14 16:00:33 by dabae            ###   ########.fr       */
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
			err_msg_exit("unable to get commands", args_cmds);
		pipex_bonus(ac, av, args_cmds, envp);
		free_triple_arr(args_cmds);
		return (EXIT_SUCCESS);
	}
	else
		err_msg_exit("Not enough arguments", NULL);
}
