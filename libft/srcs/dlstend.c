/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:04:00 by jessy             #+#    #+#             */
/*   Updated: 2021/10/31 02:04:43 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*dlst_end(t_dlist *list)
{
	t_dlist	*iter;

	iter = list;
	while (iter->next)
	{
		iter = iter->next;
	}
	return (iter);
}
