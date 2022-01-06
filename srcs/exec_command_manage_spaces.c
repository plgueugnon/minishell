/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_manage_spaces.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:16:23 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/17 19:21:01 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_not_only_void_before(t_token *token1, t_dlist *dlsttmp1,
			t_dlist **list)
{
	t_dlist	*tmp;
	t_dlist	*iter;

	iter = dlsttmp1;
	if (iter->prev)
	{
		iter = iter->prev;
		token1 = iter->content;
		tmp = iter;
		while (iter)
		{
			token1 = iter->content;
			if (token1->type != 2)
				return ;
			if (!iter->prev)
				break ;
			iter = iter->prev;
		}
		clear_sublst(iter, tmp);
		*list = dlsttmp1;
		g_info.cmd = dlsttmp1;
	}
}

static void	print_newline_error_msg(void)
{
	ft_putstr_fd("bash: syntax error near ", 2);
	ft_putstr_fd("unexpected token `newline'\n", 2);
	clear_cmd_lst(&g_info.cmd);
	errno = 1;
}

int	check_command2(t_token *token1, t_dlist *dlsttmp1, t_dlist *list)
{
	t_dlist	*tmp;

	tmp = dlsttmp1;
	if (token1->type != 2)
		check_not_only_void_before(token1, dlsttmp1, &list);
	if (token1->type == 2)
	{
		while (token1->type == 2)
		{
			if (!dlsttmp1->prev)
			{
				clear_sublst(dlsttmp1, tmp);
				return (1);
			}
			else
				dlsttmp1 = dlsttmp1->prev;
			token1 = dlsttmp1->content;
		}
		if (token1->type >= 3 && token1->type <= 6)
		{
			print_newline_error_msg();
			return (1);
		}
	}
	return (check_command3(token1, dlsttmp1, list));
}
