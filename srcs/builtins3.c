/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 00:58:37 by jessy             #+#    #+#             */
/*   Updated: 2021/11/17 18:53:26 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env2(char *cmd)
{
	int			i;
	struct stat	sb;

	i = 3;
	while (cmd[i] == ' ')
		i++;
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(&cmd[i], 2);
	if (!stat(&cmd[i], &sb))
	{
		ft_putstr_fd("’: Permission denied\n", 2);
		errno = 126;
	}
	else
	{
		ft_putstr_fd("’: No such file or directory\n", 2);
		errno = 127;
	}
}

void	env(char *cmd, int fd)
{
	t_list		*tmp;
	int			i;

	i = 3;
	tmp = g_info.env;
	while (cmd[i] == ' ')
		i++;
	if (ft_strcmp(cmd, "env") && cmd[i])
		env2(cmd);
	else
	{
		while (tmp)
		{
			ft_putstr_fd(tmp->content, fd);
			ft_putstr_fd("\n", fd);
			tmp = tmp->next;
		}
		errno = 0;
	}
}

void	echo2(char **cmd, int *i, int *j, int *returnendline)
{
	while ((*cmd)[*i + *j] && (*cmd)[*i + *j] != ' ')
	{
		if ((*cmd)[*i + *j] != 'n')
			break ;
		(*j)++;
	}
	if (!(*cmd)[*i + *j] || (*cmd)[*i + *j] == ' ')
	{
		*returnendline = 1;
		*i += *j;
	}
}

void	echo(char *cmd, int fd)
{
	int	i;
	int	returnendline;
	int	j;

	i = 4;
	j = 0;
	returnendline = 0;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
	{
		i++;
		echo2(&cmd, &i, &j, &returnendline);
	}
	while (cmd[i] && cmd[i] == ' ')
		i++;
	ft_putstr_fd(&cmd[i], fd);
	if (!returnendline)
		ft_putstr_fd("\n", fd);
	errno = 0;
}
