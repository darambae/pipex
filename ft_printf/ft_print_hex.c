/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:41:04 by dabae             #+#    #+#             */
/*   Updated: 2023/10/25 14:52:05 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_count_digit(unsigned int n)
{
	int	count;

	count = 1;
	if (n > 15)
	{
		while (n > 15)
		{
			n /= 16;
			count++;
		}
	}
	return (count);
}

static void	ft_fill_hex(char *res, unsigned int n, int capital)
{
	char	*hex_up;
	char	*hex_low;

	hex_up = ft_strdup("0123456789ABCDEF");
	hex_low = ft_strdup("0123456789abcdef");
	if (!hex_up || !hex_low)
		return ;
	if (n == 0)
		*res = '0';
	else
	{
		while (n)
		{
			if (capital)
				*res-- = hex_up[n % 16];
			else
				*res-- = hex_low[n % 16];
			n /= 16;
		}
	}
	free(hex_up);
	free(hex_low);
}

int	ft_print_hex(unsigned int n, int capital)
{
	int		num_print;
	int		count;
	char	*res;

	count = ft_count_digit(n);
	if (n == 0)
		count = 1;
	res = (char *)malloc(sizeof(char) * (count + 1));
	if (!res)
		return (0);
	ft_memset(res, '\0', count + 1);
	ft_fill_hex(res + count - 1, n, capital);
	num_print = ft_print_str(res);
	free(res);
	return (num_print);
}
