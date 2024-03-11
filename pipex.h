/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:52 by dabae             #+#    #+#             */
/*   Updated: 2024/03/08 11:47:42 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/fcntl.h>
# include "libft/libft.h"

char	***trim_cmds(int ac, char **av);
char	*get_cmd_path(char *cmd_name, char **envp);
void	free_triple_arr(char ***arr);
int		error_handler(char *arr);
char	**ft_split_special(char const *s, const char *delimiters);

#endif