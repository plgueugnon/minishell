/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:42:11 by jessy             #+#    #+#             */
/*   Updated: 2021/10/29 17:43:31 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	joincmd(char **cmd, t_dlist *lst)
{
	t_dlist	*tmp1;
	t_token	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	joincmd2(lst, &i);
	if (ft_go_malloc(cmd, (sizeof(char) * i + 1)))
		return ;
	tmp1 = lst;
	while (tmp1)
	{
		i = 0;
		tmp = tmp1->content;
		while (((char *)tmp->value)[i])
			(*cmd)[j++] = ((char *)tmp->value)[i++];
		tmp1 = tmp1->next;
	}
	(*cmd)[j] = '\0';
}

void	joincmd2(t_dlist *tmp1, int *i)
{
	t_token	*tmp;

	while (tmp1)
	{
		tmp = tmp1->content;
		*i += ft_strlen((char *)tmp->value);
		tmp1 = tmp1->next;
	}
}

int	check_builtins2(char *cmd, int i)
{
	if (!ft_strncmp(cmd, "export", i))
		ft_export(cmd, 1);
	else if (!ft_strncmp(cmd, "unset", i))
		unset(cmd);
	else if (!ft_strncmp(cmd, "env", i))
		env(cmd, 1);
	else if (!ft_strncmp(cmd, "exit", i))
		ft_exit(cmd, 0);
	else
	{
		free(cmd);
		return (1);
	}
	free(cmd);
	return (0);
}
