/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:13:03 by dabae             #+#    #+#             */
/*   Updated: 2023/10/19 17:16:11 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
static const char   *hex_low = "0123456789abcdef";
static const char   *hex_up = "0123456789ABCDEF";

static	int	ft_count_digit(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
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
static void ft_fill_hex(char *res, unsigned int n, int capital)
{
    if (n == 0)
        res[0] = '0';
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
}
void	ft_print_hex(unsigned int n, t_print *set, int capital)
{
    char    res[9];
    int count;

    count = ft_count_digit(n);
    if (n < 0)
    {
        *res = '-';
        n *= -1;
    }
    else if (n == 0)
        count = 1;
    ft_fill_hex(res + count - 1, n, capital);
    if (set->preci == 0 && (set->zero || n == 0))
    {
        set->n = 0;
        return ;
    }
    else if (set->zero == 1 && set->left == 1)
    {
        set->n = 0;
        return ;
    }
}
