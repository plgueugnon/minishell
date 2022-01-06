/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbcollector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:57:50 by jessy             #+#    #+#             */
/*   Updated: 2021/11/07 22:20:48 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clearmaillon(t_gbc *lst)
{
	if (lst->type == TOKEN)
		clear_cmd_lst((t_dlist **)&lst->str);
	else
		gbcclear((t_gbc **)&lst->str);
	free(lst);
}

void	gbcclear(t_gbc **alst)
{
	t_gbc	*tmp;

	while (*alst)
	{
		tmp = *alst;
		*alst = (*alst)->next;
		clearmaillon(tmp);
	}
	*alst = 0;
}

void	gbcclear_one(t_gbc **alst, int maillon, int size)
{
	t_gbc	*tmp;
	t_gbc	*tmp2;
	int		i;

	tmp = *alst;
	tmp2 = 0;
	i = 0;
	while (i < maillon)
	{
		if (i == maillon - 1)
			tmp2 = tmp;
		tmp = tmp->next;
		i++;
	}
	if (maillon != size)
	{
		if (!tmp2)
			(*alst) = (*alst)->next;
		else
			tmp2->next = tmp->next;
	}
	else
		tmp2->next = 0;
	clearmaillon(tmp);
}

t_gbc	*newgbc(int type, int fd, void *str)
{
	t_gbc	*new;

	if (ft_go_malloc((void *)&new, sizeof(t_gbc)))
		return (0);
	new->type = type;
	new->fd = fd;
	new->str = str;
	new->next = 0;
	return (new);
}

void	lstaddback_gbc(t_gbc **alst, t_gbc *new)
{
	t_gbc	*tmp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
