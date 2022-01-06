/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstfind_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:04:03 by jessy             #+#    #+#             */
/*   Updated: 2021/10/31 02:04:55 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*dlstfind_node(t_dlist *list, void *content)
{
	t_dlist	*tmp;

	tmp = list;
	while (tmp)
	{
		if (!ft_memcmp(tmp->content, content, ft_strlen((char *)content)))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}
