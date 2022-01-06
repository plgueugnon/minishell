/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:49:52 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/12 21:55:01 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concate_node(t_dlist **sub, t_token_type type)
{
	t_token	*token;
	char	*tmp;
	char	*buf;

	buf = ft_strdup("");
	tmp = NULL;
	if (!buf)
		clear_buffer(buf, tmp);
	while (*sub)
	{
		if (find_token_type(type, (*sub)->content))
			break ;
		token = (*sub)->content;
		tmp = buf;
		buf = ft_strjoin(buf, token->value);
		if (!buf)
			clear_buffer(buf, tmp);
		ft_memdel((void *)&tmp);
		*sub = (*sub)->next;
	}
	return (buf);
}

t_dlist	*concate_quoted(t_dlist *sub, t_token_type type)
{
	char	*buf;
	t_dlist	*begin;
	t_dlist	*new;
	t_token	*token;

	begin = sub;
	sub = sub->next;
	buf = concate_node(&sub, type);
	if (!sub)
	{
		ft_memdel((void *)&buf);
		return (begin->next);
	}
	if (begin->next != sub)
	{
		new = dlstnew(ft_malloc_token(buf, literal, 0, ft_strlen(buf)));
		if (!new)
			clear_buffer(buf, 0);
		token = new->content;
		token->qstat = lit_quoted;
		dlstinsert_node(&g_info.cmd, sub, new);
	}
	ft_memdel((void *)&buf);
	return (clean_sublst(begin, sub));
}

void	parse_quote(void)
{
	t_dlist	*iter;

	iter = g_info.cmd;
	while (iter)
	{
		if (iter && find_token_type(sgle_quote, iter->content))
			iter = concate_quoted(iter, sgle_quote);
		if (iter && find_token_type(dble_quote, iter->content))
			iter = concate_quoted(iter, dble_quote);
		if (iter && find_token_type(sgle_quote, iter->content))
			iter = concate_quoted(iter, sgle_quote);
		if (iter)
			iter = iter->next;
	}
	return ;
}
