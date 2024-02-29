/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:58:27 by dabae             #+#    #+#             */
/*   Updated: 2023/10/25 11:20:00 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static	int	ft_print_holder(const char *str, int n, va_list ap)
{
	int	num_print;

	num_print = 0;
	if (str[n] == 'c')
		num_print += ft_print_char(va_arg(ap, int));
	else if (str[n] == 's')
		num_print += ft_print_str(va_arg(ap, const char *));
	else if (str[n] == 'p')
		num_print += ft_print_pointer((unsigned long long)va_arg(ap, void *));
	else if (str[n] == 'd' || str[n] == 'i')
		num_print += ft_print_int(va_arg(ap, int));
	else if (str[n] == 'x')
		num_print += ft_print_hex(va_arg(ap, unsigned int), 0);
	else if (str[n] == 'X')
		num_print += ft_print_hex(va_arg(ap, unsigned int), 1);
	else if (str[n] == 'u')
		num_print += ft_print_unsigned(va_arg(ap, unsigned int));
	else if (str[n] == '%')
		num_print += write(1, "%", 1);
	return (num_print);
}

static	int	ft_parse_format(const char *str, va_list ap)
{
	int	i;
	int	num_print;

	num_print = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr("cspdixXu%", str[i + 1]) && str[i + 1])
		{
			num_print += ft_print_holder(str, i + 1, ap);
			i++;
		}
		else
			num_print += write(1, &str[i], 1);
		i++;
	}
	return (num_print);
}

int	ft_printf(const char *format, ...)
{
	int		res;
	va_list	ap;

	if (!format)
		return (0);
	res = 0;
	va_start(ap, format);
	res = ft_parse_format(format, ap);
	va_end(ap);
	return (res);
}
