/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:50:33 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/12 21:50:29 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token(t_dlist *list, t_token *token)
{
	ft_memdel(&token->value);
	ft_memdel(&list->content);
	ft_memdel((void *)&list);
}

void	clear_cmd_lst(t_dlist **lst)
{
	t_dlist	*tmp;
	t_token	*token;

	tmp = NULL;
	token = NULL;
	if (*lst)
	{
		while (*lst)
		{
			tmp = *lst;
			token = tmp->content;
			*lst = (*lst)->next;
			clear_token(tmp, token);
		}
	}
	*lst = NULL;
}

int	clear_cmd_node(t_dlist **lst)
{
	t_dlist	*tmp;

	tmp = *lst;
	if (!(*lst)->prev)
	{
		*lst = (*lst)->next;
		if (*lst)
			(*lst)->prev = NULL;
		g_info.cmd = *lst;
		if (g_info.nbpipe && g_info.cmdpipe)
			g_info.cmdpipe->content = *lst;
	}
	else if (!(*lst)->next)
	{
		*lst = (*lst)->prev;
		(*lst)->next = NULL;
	}
	else if ((*lst)->prev && (*lst)->next)
	{
		*lst = (*lst)->next;
		(*lst)->prev = tmp->prev;
		tmp->prev->next = *lst;
	}
	clear_token(tmp, tmp->content);
	return (0);
}

void	free_dbl(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i--)
		free(str[i]);
	free(str);
	str = 0;
}
