/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:45:29 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/17 18:46:10 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset3(t_list **tmp, t_list **tmp2, int *i)
{
	*tmp = g_info.env;
	while (*i - 1)
	{
		*tmp = (*tmp)->next;
		(*i)--;
	}
	(*tmp)->next = *tmp2;
}

void	unset2(char *cmd, int j)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*tfchier;
	int		i;

	tmp = g_info.env;
	i = 0;
	while (tmp)
	{
		tfchier = tmp->content;
		if (!ft_strncmp(tmp->content, cmd, j)
			&& (tfchier[j] == '=' || !tfchier[j]))
		{
			tmp2 = tmp->next;
			free(tmp->content);
			free(tmp);
			if (i)
				unset3(&tmp, &tmp2, &i);
			else
				g_info.env = tmp2;
			break ;
		}
		tmp = tmp->next;
		i++;
	}
}

void	unset(char *cmd)
{
	int		j;
	int		k;
	char	**cmdsplit;

	k = 1;
	cmdsplit = ft_split(cmd, ' ');
	while (cmdsplit[k])
	{
		j = -1;
		while (cmdsplit[k][++j])
		{
			if (!ft_isalnum(cmdsplit[k][j]) && cmdsplit[k][j] != '_')
			{
				ft_putstr_fd("unset: '", 2);
				ft_putstr_fd(cmdsplit[k], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				errno = 1;
				return ;
			}
		}
		unset2(cmdsplit[k], j);
		errno = 0;
		k++;
	}
	free_dbl(cmdsplit);
}
