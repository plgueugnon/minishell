/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:29:26 by jessy             #+#    #+#             */
/*   Updated: 2021/11/12 21:57:36 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(void)
{
	t_dlist	*tmp;
	t_token	*token;
	t_dlist	*tmp1;

	tmp1 = g_info.cmd;
	while (tmp1)
	{
		token = tmp1->content;
		if (token->type == pipeline)
		{
			tmp = tmp1->next;
			if (tmp)
				token = tmp->content;
			while (tmp && token->type != 0 && token->type != literal)
			{
				tmp = tmp->next;
				if (tmp)
					token = tmp->content;
			}
			if (check_pipe2(tmp, token))
				return (1);
		}
		tmp1 = tmp1->next;
	}
	return (0);
}

int	check_error_pipe2(void)
{
	t_dlist	*tmp;
	t_token	*token;

	tmp = g_info.cmd;
	token = tmp->content;
	while (tmp && (token->type == space || token->type == pipeline))
	{
		tmp = tmp->next;
		if (tmp)
			token = tmp->content;
	}
	if (!tmp)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		clear_cmd_lst(&g_info.cmd);
		errno = 2;
		return (1);
	}
	return (0);
}

int	check_error_pipe(void)
{
	t_dlist	*tmp;
	t_token	*token;

	if (dlstsize(g_info.cmd) == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		clear_cmd_lst(&g_info.cmd);
		errno = 2;
		return (1);
	}
	tmp = g_info.cmd;
	token = tmp->content;
	if (token->type == pipeline)
	{
		tmp = tmp->next;
		token = tmp->content;
		if (token->type == pipeline)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			clear_cmd_lst(&g_info.cmd);
			errno = 2;
			return (1);
		}
	}
	return (check_error_pipe2());
}

void	parse_token2(void)
{
	parse_env();
	parse_quote();
	if (g_info.nbpipe)
	{
		if (check_error_pipe())
			return ;
		if (check_pipe())
			return ;
	}
	if (g_info.nbpipe)
		create_pipeline();
	else
		expand_env();
}

void	parse_token(void)
{
	t_dlist	*iter;

	iter = g_info.cmd;
	g_info.nbpipe = 0;
	while (iter)
	{
		if (find_token_type(pipeline, iter->content))
		{
			if (!is_it_literal(iter, iter->content))
				g_info.nbpipe++;
		}
		if (find_token_type(dollar, iter->content))
			is_it_literal(iter, iter->content);
		if (find_token_type(dollar, iter->content))
			check_if_quoted(iter, iter->content);
		iter = iter->next;
	}
	parse_token2();
}
