/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:01:52 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/01 11:13:37 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_append(t_list *list, void *content)
{
	t_list	**plist;

	if (!list || !content)
		return (NULL);
	plist = &list;
	while (*plist)
		plist = &(*plist)->next;
	*plist = ft_lstnew(content);
	if (*plist)
		return (list);
	else
		return (NULL);
}
