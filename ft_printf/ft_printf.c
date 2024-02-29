/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:41:48 by dabae             #+#    #+#             */
/*   Updated: 2023/10/18 11:19:20 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

t_print	*ft_init_set(t_print *set)
{
	set->n = 0;
	set->width = 0;
	set->preci = -1;
	set->zero = 0;
	set->left = -1;
	set->plus = 0;
	set->space = 0;
	set->hash = 0;
	return (set);
}

int	ft_parse_str(const char *str, va_list ap)
{
	int	i;
	int num_print;
	t_print	*set;

	num_print = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			set = (t_print *)malloc(sizeof(t_print));
			if (!set)
				return (-1);
			ft_init_set(set);
			ft_print_holder(set, str, i + 1, ap);
			num_print += set->n;
		}
		else
			num_print += write(1, &str[i], 1);
	}
	return (num_print);
}
int	ft_printf(const char *str, ...)
{
	int	res;
	va_list	ap;

	res = 0;
	va_start(ap, str);
	res = ft_parse_str(str, ap);
	va_end(ap);
	return (res);
}
