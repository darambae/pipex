/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:24:38 by dabae             #+#    #+#             */
/*   Updated: 2023/10/25 15:46:51 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_count_digit(unsigned long long n)
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

static void	ft_fill_hex(char *res, unsigned long long n)
{
	char	*hex;

	hex = ft_strdup("0123456789abcdef");
	if (!hex)
		return ;
	if (n == 0)
	{
		*res = '0';
		free(hex);
		return ;
	}
	while (n)
	{
		*res-- = hex[n % 16];
		n /= 16;
	}
	free(hex);
}

int	ft_print_pointer(unsigned long long n)
{
	int		num;
	int		count;
	char	*res;

	num = 0;
	if (n == 0)
		return (write(1, "(nil)", 5));
	count = ft_count_digit(n);
	res = (char *)malloc(sizeof(char) * (count + 1));
	ft_memset(res, '\0', count + 1);
	ft_fill_hex(res + count - 1, n);
	num += ft_print_str("0x");
	num += ft_print_str(res);
	free(res);
	return (num);
}
