/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:50:17 by pgueugno          #+#    #+#             */
/*   Updated: 2021/10/30 18:30:22 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_path2(char **path, char *buff, char *color, int i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (color[k] != '|')
		(*path)[j++] = color[k++];
	while (buff[i])
		(*path)[j++] = buff[i++];
	(*path)[j++] = ' ';
	(*path)[j++] = '>';
	(*path)[j++] = '>';
	(*path)[j++] = ' ';
	while (color[++k])
		(*path)[j++] = color[k];
	(*path)[j] = '\0';
}

int	ft_get_path(char **path, char *buff, char *color)
{
	int	i;

	i = 0;
	if (!buff)
	{
		*path = ft_strdup("\033[1;35m?>>\033[0m");
		return (1);
	}
	while (buff[i])
		i++;
	while (i > 0 && buff[i] != '/')
		i--;
	i++;
	if (ft_go_malloc(path,
			(sizeof(char) * (strlen(buff) - i + 4 + strlen(color)))))
		return (0);
	ft_get_path2(path, buff, color, i);
	return (1);
}

int	catch_eof_signal(char *line, char *path)
{
	if (!line)
	{
		if (g_info.tmperrno)
			errno = g_info.tmperrno;
		free(line);
		free(path);
		ft_exit(0, no_err);
	}
	return (1);
}

char	*get_prompt(void)
{
	char	*path;
	char	*tmp;
	char	*ret;

	if (!ft_get_path(&path, g_info.pwd, "\033[1;35m|\033[0m"))
		ft_exit(0, err_malloc);
	tmp = readline(path);
	catch_eof_signal(tmp, path);
	ret = ft_strtrim(tmp, " ");
	free(tmp);
	free(path);
	return (ret);
}
