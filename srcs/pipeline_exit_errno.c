/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exit_errno.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:59:35 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/17 18:59:42 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_exit(t_dlist *list)
{
	t_dlist	*tmp;
	t_token	*token;

	while (list->next)
		list = list->next;
	tmp = list->content;
	if (!tmp)
		return ;
	token = tmp->content;
	if (!strcmp((char *)token->value, "exit"))
	{
		tmp = tmp->next;
		if (tmp)
			check_if_exit2(tmp);
	}
}

void	set_errno_value(char *str, int i)
{
	errno = ft_atoll(str, &i);
	if (errno < 0)
		errno += 256;
	errno %= 256;
}

void	check_if_exit2(t_dlist	*tmp)
{
	char	*str;
	t_token	*token;
	int		i;

	i = 0;
	token = tmp->content;
	if (token->type == space)
	{
		tmp = tmp->next;
		if (tmp)
		{
			token = tmp->content;
			str = token->value;
			if (str[i] == '-')
				i++;
			while (ft_isdigit(str[i]))
				i++;
			if (!str[i])
				set_errno_value(str, i);
			else
				errno = 2;
			if (tmp->next)
				errno = 1;
		}
	}
}
