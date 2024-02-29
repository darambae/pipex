/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:49:30 by dabae             #+#    #+#             */
/*   Updated: 2023/10/18 11:19:35 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <string.h>

# define HEX_UP "0123456789ABCDEF"
# define HEX_LOW "0123456789abcdef"

typedef	struct	s_print
{
	int	n;
	int	width;
	int	preci;
	int	zero;
	int	left;
	int	plus;
	int	space;
	int	hash;
}	t_print;




#endif
