/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:35:01 by dabae             #+#    #+#             */
/*   Updated: 2024/03/14 15:58:07 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

char	***trim_cmds(int ac, char **av);
char	*get_cmd_path(char *cmd_name, char **envp);
void	free_triple_arr(char ***arr);
void	err_msg_exit(char *msg, char ***arr);
int		pipex_bonus(int ac, char **av, char ***cmds, char **envp);
char	**ft_split_special(char const *s, const char *delimiters);

#endif