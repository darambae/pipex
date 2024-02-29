/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:51:52 by dabae             #+#    #+#             */
/*   Updated: 2024/02/29 09:44:40 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_pipe
{
	char	*infile;
	char	*outfile;
	int		in_fd;
	int		out_fd;
	bool	here_doc;
	char	***cmd_args;
	char	*paths;
}	t_pipe;

#endif