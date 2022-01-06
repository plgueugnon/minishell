/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:09:23 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/15 15:22:48 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_is_quoted(t_dlist **iter, t_dlist *node, t_token *src)
{
	t_token			*token;
	t_token_type	type;
	int				flag;

	token = (*iter)->content;
	type = token->type;
	flag = 1;
	if ((*iter)->next)
		*iter = (*iter)->next;
	while (*iter)
	{
		token = (*iter)->content;
		if (*iter == node)
			flag = 0;
		if (token->type == type && !flag)
		{
			src->qstat = env_quoted;
			return (1);
		}
		else if (token->type == type && flag)
			return (0);
		*iter = (*iter)->next;
	}
	return (0);
}

int	check_if_quoted(t_dlist *node, t_token *token)
{
	t_dlist	*iter;
	t_token	*access;

	if (node->next)
	{
		access = node->next->content;
		iter = g_info.cmd;
		while (iter && iter != node)
		{
			if ((token->type == dollar)
				&& find_token_type(dble_quote, iter->content))
			{
				if (next_is_quoted(&iter, node, node->content))
					access->qstat = env_quoted;
			}
			if (iter)
				iter = iter->next;
		}
	}
	return (0);
}
