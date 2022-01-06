/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:29:40 by jessy             #+#    #+#             */
/*   Updated: 2021/10/31 02:30:36 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirecterr(t_gbc *allcmd)
{
	t_dlist	*tmp;
	t_token	*token;

	while (allcmd)
	{
		tmp = allcmd->str;
		token = tmp->content;
		if (token->type >= 3 && token->type <= 6)
		{
			if (tmp->next)
				token = tmp->next->content;
			if (!tmp->next || (token->type >= 3 && token->type <= 6))
			{
				ft_putstr_fd("bash: syntax error near unexpected token `", 2);
				ft_putstr_fd((char *)token->value, 2);
				ft_putstr_fd("'\n", 2);
				errno = 2;
				return (1);
			}
		}
		allcmd = allcmd->next;
	}
	return (0);
}

int	check_directory2(char *str, char **dir)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_dbl(dir);
	errno = 1;
	return (1);
}

int	check_directory(char *str)
{
	char	**dir;
	int		i;
	int		j;

	j = 0;
	dir = ft_split(str, '/');
	while (dir[j])
		j++;
	if (j > 1)
	{
		i = 0;
		while (dir[i] && i < j - 1)
		{
			if (check_exist(dir[i]))
				return (check_directory2(str, dir));
			i++;
		}
	}
	free_dbl(dir);
	return (0);
}

int	createfile2err(t_token *token, DIR *check)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd((char *)token->value, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	closedir(check);
	errno = 1;
	return (1);
}

int	createfile2b(t_token *token)
{
	int	fd;

	if (check_directory((char *)token->value))
		return (1);
	fd = open((char *)token->value, O_CREAT, 0664);
	if (fd < 0)
		ft_exit(0, err_fd);
	close(fd);
	g_info.redir_right = 1;
	return (0);
}
