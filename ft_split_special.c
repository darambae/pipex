/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:19:17 by dabae             #+#    #+#             */
/*   Updated: 2024/03/08 16:41:19 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ft_count_arr : to count the number of the words in the string seperated 
 by delimiters */

static int	ft_count_arr(char const *s, const char *delimiters)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_strchr(delimiters, s[i]))
		{
			count++;
			while (s[i] && !ft_strchr(delimiters, s[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}

/* ft_size_wd : to count the length of a word till encountering 
 the delimiters */

static int	ft_size_wd(char const *s, const char *delimiters, int i)
{
	int	size;

	size = 0;
	while (s[i] && !ft_strchr(delimiters, s[i]))
	{
		size++;
		i++;
	}
	return (size);
}

/* ft_split_special: to manage the cases of the arguments with space, 
 single quote and double quote. */

char	**ft_split_special(char const *s, const char *delimiters)
{
	char	**arrs;
	int		i;
	int		z;
	int		size;

	arrs = (char **)malloc(sizeof(char *) * (ft_count_arr(s, delimiters) + 1));
	if (!arrs)
		return (NULL);
	i = 0;
	z = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(delimiters, s[i]))
			i++;
		if (!s[i])
			break ;
		size = ft_size_wd(s, delimiters, i);
		arrs[z] = ft_substr(s, i, size);
		if (!arrs[z])
			return (ft_free_tab(arrs));
		z++;
		i += size;
	}
	arrs[z] = NULL;
	return (arrs);
}
