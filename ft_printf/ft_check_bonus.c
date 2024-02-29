#include "ft_printf.h"

void	ft_set_flag(t_print *set, const char *str, int pos)
{
	if (str[pos] == ' ')
		set->space = 1;
	if (str[pos] == '.')
	{
		set->preci = 0;
		while (ft_isdigit(str[++pos]))
			set->preci = set->preci * 10 + str[pos] - '0';
	}
	if (str[pos] == '0')
		set->zero = 1;
	if (str[pos] == '#')
		set->hash = 1;
	if (str[pos] == '-')
		set->minus = 1;
	if (str[pos] == '+')
		set->plus = 1;
}

void	ft_set_width(t_print *set, const char *str, int pos)
{
	while (ft_isdigit(str[pos]))
	{
		set->width = set->width * 10 + str[pos] - '0';
		pos++;
	}
	return (pos);
}