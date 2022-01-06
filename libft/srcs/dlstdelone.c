/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstdelone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:03:57 by jessy             #+#    #+#             */
/*   Updated: 2021/10/31 02:03:58 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dlstdelone(t_dlist **lst, void (*del)(void **))
{
	t_dlist	*tmp;

	if (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		(*lst)->prev = tmp->prev;
		tmp->prev->next = *lst;
		del(&tmp->content);
		free(tmp);
	}
}
