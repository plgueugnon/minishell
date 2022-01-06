/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstinsert_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:04:06 by jessy             #+#    #+#             */
/*   Updated: 2021/10/31 02:04:07 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dlstinsert_node(t_dlist **alst, t_dlist *pos, t_dlist *new)
{
	t_dlist	*iter;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	iter = *alst;
	if (pos)
	{
		while (iter != pos)
			iter = iter->next;
		if (!pos->next)
		{
			dlstadd_back(alst, new);
			return ;
		}
		new->next = iter->next;
		iter->next->prev = new;
		iter->next = new;
		new->prev = iter;
	}
}
