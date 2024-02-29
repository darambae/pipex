/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:43:12 by dabae             #+#    #+#             */
/*   Updated: 2023/10/25 14:41:20 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_print_int(int n)
{
	char	*arr;
	int		num_print;

	arr = ft_itoa(n);
	num_print = ft_print_str(arr);
	free(arr);
	return (num_print);
}
