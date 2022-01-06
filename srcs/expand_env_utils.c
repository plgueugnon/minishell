/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:50:30 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/12 22:13:59 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_a_space(char *str)
{
	while (*str)
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

int	valid_env_char(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || c == 95)
		return (1);
	return (0);
}

void	replace_node_value(char **evar, t_dlist **iter)
{
	t_token	*token;
	char	*tmp;
	int		f;

	f = 0;
	tmp = *evar;
	token = (*iter)->content;
	ft_memdel(&token->value);
	while (*tmp)
	{
		if (*tmp == '=' && !f)
		{
			tmp++;
			token->value = ft_strdup(tmp);
			f = 1;
		}
		if (*tmp != '\0')
			tmp++;
	}
	free(*evar);
}

int	find_errno_type(t_dlist *lst)
{
	t_token	*token;

	if (lst)
	{
		token = lst->content;
		if (token->type == dollar && lst->next)
		{
			lst = lst->next;
			token = lst->content;
			if (!strcmp((char *)token->value, "?"))
				return (1);
		}
	}
	return (0);
}

void	replace_errno(char *str, t_dlist **lst)
{
	t_dlist	*tmp;
	t_token	*token;

	tmp = (*lst)->next;
	(*lst)->next = tmp->next;
	clear_cmd_node(&tmp);
	token = (*lst)->content;
	token->type = literal;
	free(token->value);
	token->value = ft_strdup(str);
	free(str);
}
