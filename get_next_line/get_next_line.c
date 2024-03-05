/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:15 by dabae             #+#    #+#             */
/*   Updated: 2024/03/04 11:18:34 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static  void	extract_rest(t_line *buf_list, char **rest)
{
	t_line	*last_node = NULL;

	last_node = NULL;
		while (buf_list)
	{
		last_node = buf_list;
		buf_list = buf_list->next;
	}
	copy_rest(last_node, rest);
}

static void	retrieve_line(t_line *buf_list, char **line)
{
	int	i;
	int	j;

	*line = (char *)malloc(sizeof(char) * (line_len(buf_list) + 1));
	if (!*line)
		return ;
	j = 0;
	while (buf_list)
	{
		i = 0;
		while (buf_list->str_tmp[i] && buf_list->str_tmp[i] != '\n')
		{
			(*line)[j] = buf_list->str_tmp[i];
			i++;
			j++;
		}
		if (buf_list->str_tmp[i] == '\n')
		{
			(*line)[j] = '\0';
			return ;
		}
	buf_list = buf_list->next;
	}
	(*line)[j] = '\0';
}

static	int	found_n(t_line *buf_list)
{
	int	i;

	while (buf_list)
	{
		i = 0;
		while (buf_list->str_tmp[i] && i < BUFFER_SIZE)
		{
			if (buf_list->str_tmp[i] == '\n')
				return (1);
			i++;
		}
		buf_list = buf_list->next;
	}
	return (0);
}
static	void	create_list(t_line **buf_list, int fd)
{
	char    *buffer;
	int     bytes_read;

	while (!found_n(*buf_list))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
		{
			free_list(*buf_list);
			return ;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			buffer = malloc(sizeof(char) * 2);
			if (!buffer)
			{
				free_list(*buf_list);
				return ;
			}
			buffer[0] = '\n';
			buffer[1] = '\0';
			add_node(buf_list, buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		add_node(buf_list, buffer);
	}
}
char	*get_next_line(int fd)
{
	static	t_line	*buf_list;
	char	*line;
	char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&buf_list, fd);
	line = NULL;
	retrieve_line(buf_list, &line);
	rest = NULL;
	extract_rest(buf_list, &rest);
	if (rest && buf_list)
	{
		empty_attach_node(&buf_list, rest);
		free(rest);
	}
	return (line);
}
