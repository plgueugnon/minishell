/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlstnew.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:04:10 by jessy             #+#    #+#             */
/*   Updated: 2021/10/31 02:05:10 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*dlstnew(void *content)
{
	t_dlist	*l_init;

	if (!content)
		return (0);
	l_init = malloc(sizeof(t_dlist));
	if (!l_init)
		return (0);
	else
	{
		l_init->content = content;
		l_init->next = NULL;
		l_init->prev = NULL;
	}
	return (l_init);
}
