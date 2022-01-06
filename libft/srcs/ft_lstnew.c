/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:09:03 by pgueugno          #+#    #+#             */
/*   Updated: 2021/01/06 15:56:33 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l_init;

	l_init = malloc(sizeof(t_list));
	if (l_init == NULL)
		return (0);
	if (l_init)
	{
		l_init->content = content;
		l_init->next = NULL;
	}
	return (l_init);
}
