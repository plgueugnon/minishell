/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:48:28 by jessy             #+#    #+#             */
/*   Updated: 2021/11/12 21:41:00 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_identical_token(t_dlist **iter, t_dlist *node, t_token *src)
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
			src->type = literal;
			return (1);
		}
		else if (token->type == type && flag)
			return (0);
		*iter = (*iter)->next;
	}
	return (0);
}

int	is_it_literal(t_dlist *node, t_token *token)
{
	t_dlist	*iter;

	iter = g_info.cmd;
	while (iter && iter != node)
	{
		if (token->type != dollar
			&& (find_token_type(sgle_quote, iter->content)
				|| find_token_type(dble_quote, iter->content)))
		{
			if (next_identical_token(&iter, node, node->content))
				return (1);
		}
		if (token->type == dollar
			&& find_token_type(sgle_quote, iter->content))
		{
			if (next_identical_token(&iter, node, node->content))
				return (1);
		}
		if (iter)
			iter = iter->next;
	}
	return (0);
}

int	check_pipe2(t_dlist *tmp, t_token *token)
{
	if (!tmp || (token->type == pipeline && !tmp->next))
	{
		ft_putstr_fd("bash: syntax error", 2);
		ft_putstr_fd("near unexpected token `|'\n", 2);
		errno = 2;
		clear_cmd_lst(&g_info.cmd);
		return (1);
	}
	else if (token->type == pipeline)
	{
		ft_putstr_fd("bash: syntax error", 2);
		ft_putstr_fd("near unexpected token `|'\n", 2);
		clear_cmd_lst(&g_info.cmd);
		errno = 2;
		return (1);
	}
	return (0);
}
