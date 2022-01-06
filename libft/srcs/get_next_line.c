/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:12:16 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 14:59:48 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_it(char **tmp, int fd)
{
	int		r;
	char	*buf;
	char	*p;

	r = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!(ft_strchr(*tmp, '\n')) && r > 0)
	{
		(r = read(fd, buf, BUFFER_SIZE));
		if (r)
		{
			buf[r] = '\0';
			p = *tmp;
			*tmp = ft_strjoin(*tmp, (char *)buf);
			free(p);
		}
	}
	free(buf);
	buf = NULL;
	return (*tmp);
}

int	ft_what_is_read(char **tmp, char **line)
{
	char	*p;
	char	*mem;

	p = NULL;
	if (ft_strchr(*tmp, '\n') == 0)
	{
		*line = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
		return (0);
	}
	else if (ft_strchr(*tmp, '\n') != 0)
	{
		mem = ft_strchr(*tmp, '\n');
		*line = malloc(sizeof(char) * (mem - *tmp + 1));
		if (!(*line))
			return (-1);
		*line = ft_strncpy(*line, *tmp, (mem - *tmp));
		p = *tmp;
		*tmp = ft_strdup(mem + 1);
		free(p);
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*tmp = NULL;

	if (line == NULL || fd < 0 || read(fd, tmp, 0) < 0 || BUFFER_SIZE < 0)
		return (-1);
	if (!tmp)
		tmp = ft_strdup("");
	if (!tmp)
		return (-1);
	if (BUFFER_SIZE == 0)
	{
		*line = NULL;
		return (0);
	}
	tmp = ft_read_it(&tmp, fd);
	return (ft_what_is_read(&tmp, line));
}
