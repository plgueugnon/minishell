/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparse_expanded_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:10:28 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/17 18:22:07 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_node_in_pipe(t_dlist **tmp, t_dlist *new)
{
	t_dlist	*iter;

	iter = g_info.cmdpipe->content;
	dlstinsert_node(&iter, *tmp, new);
}

void	adjust_position(t_dlist **begin, t_dlist *end)
{
	t_dlist	*iter;

	iter = *begin;
	while (iter->next)
	{
		iter = iter->next;
	}
	iter->next = end;
	if (end)
		end->prev = iter;
}

void	add_space_node(t_dlist **iter, t_dlist *new)
{
	new = dlstnew(ft_malloc_token(" ", space, 0, 1));
	dlstadd_back(iter, new);
}

static void	retokenize_rest(t_dlist **iter, char *str, int i)
{
	char	**split;
	t_dlist	*new;
	t_dlist	*tmp;
	int		j;

	tmp = (*iter)->next;
	(*iter)->next = NULL;
	new = dlstnew(ft_malloc_token(" ", space, 0, 1));
	dlstadd_back(iter, new);
	str = ft_strchr(str, ' ');
	split = ft_split(str, ' ');
	j = 0;
	while (split[j])
		j++;
	while (split[i])
	{
		new = dlstnew(ft_malloc_token(split[i], literal, 0, ft_strlen(str)));
		dlstadd_back(iter, new);
		if (i < j - 1)
			add_space_node(iter, new);
		i++;
	}
	adjust_position(iter, tmp);
	clean_split(split);
}

void	reparse_expanded_value(t_dlist **iter)
{
	char	*str;
	t_token	*token;
	int		i;

	i = 0;
	token = (*iter)->content;
	if (token->qstat == env_quoted)
		return ;
	str = token->value;
	if (is_there_a_space(token->value))
	{
		while (str[i])
		{
			if (str[i] == ' ')
				break ;
			i++;
		}
		token->value = ft_strndup(str, i);
		i = 0;
		retokenize_rest(iter, str, i);
		free(str);
		if (dlstsize(*iter) > 2)
			token->qstat = dollar;
	}
}
