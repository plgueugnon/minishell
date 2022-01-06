/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:06:57 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/12 22:07:04 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_begin_and_end(t_dlist **iter, t_dlist *begin, t_dlist *end)
{
	if (!end)
	{
		clear_sublst((*iter)->next, end);
		begin->next = NULL;
	}
	else
	{
		clear_sublst((*iter)->next, end->prev);
		begin->next = end;
		end->prev = begin;
	}
}

void	concat_all(t_dlist **iter, t_dlist *begin, t_dlist *end, t_dlist *tmp)
{
	char	*tmp2;
	char	*tmp3;
	t_token	*tok;

	tok = tmp->content;
	tmp2 = tok->value;
	tmp = tmp->next;
	while (tmp != end)
	{
		tok = tmp->content;
		tmp3 = ft_strjoin(tmp2, tok->value);
		free(tmp2);
		tmp2 = tmp3;
		tmp = tmp->next;
	}
	tok = begin->content;
	tok->value = tmp3;
	link_begin_and_end(iter, begin, end);
}

void	find_close_litvalue(t_dlist	**iter)
{
	t_dlist	*begin;
	t_dlist	*end;
	int		i;
	t_dlist	*tmp;

	i = 0;
	begin = *iter;
	end = *iter;
	while (end)
	{
		if (!find_token_type(literal, end->content))
			break ;
		end = end->next;
	}
	tmp = begin;
	while (tmp != end)
	{
		i++;
		tmp = tmp->next;
	}
	if (i <= 1)
		return ;
	tmp = begin;
	concat_all(iter, begin, end, tmp);
}

void	concat_narrow_litvalue(void)
{
	t_dlist	*iter;

	if (g_info.nbpipe)
		iter = g_info.cmdpipe->content;
	else
		iter = g_info.cmd;
	find_close_litvalue(&iter);
}
