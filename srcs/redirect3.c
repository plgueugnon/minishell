/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:30:46 by jessy             #+#    #+#             */
/*   Updated: 2021/11/17 18:28:39 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	createfile2(t_dlist *tmp, t_token *token)
{
	struct stat	sb;
	DIR			*check;

	while (tmp && token->type != 9)
	{
		tmp = tmp->next;
		token = tmp->content;
	}
	if (token->qstat == dollar)
	{
		ambiguous_redirect_msg(token);
		return (1);
	}
	if (stat((char *)token->value, &sb))
	{
		if (createfile2b(token))
			return (1);
	}
	else
	{
		check = opendir((char *)token->value);
		if (check)
			return (createfile2err(token, check));
	}
	return (0);
}

int	createfile3(t_dlist *tmp, t_token *token, int i)
{
	if (g_info.dlb_redir_left_str)
		ft_lstclear(&g_info.dlb_redir_left_str, &ft_memdel);
	while (tmp->next)
		tmp = tmp->next;
	token = tmp->content;
	if (check_exist((char *)token->value))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd((char *)token->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		errno = 1;
		return (1);
	}
	g_info.redir_left = i;
	return (0);
}

int	createfile4(t_dlist *tmp, t_token *token, int i)
{
	char	*str;

	str = 0;
	if (g_info.dlb_redir_left_str)
		ft_lstclear(&g_info.dlb_redir_left_str, &ft_memdel);
	while (tmp->next)
		tmp = tmp->next;
	token = tmp->content;
	g_info.gnl = 0;
	g_info.stop = 0;
	while (!str || ft_strcmp(str, (char *)token->value))
	{
		g_info.gnl = 1;
		ft_putstr_fd("> ", 1);
		str = readline("");
		if (g_info.stop)
			return (createfilestop(str));
		if (ft_strrchr(str, '$') && token->qstat != lit_quoted)
			expand_dlb_left_input(&str);
		ft_lstadd_back(&g_info.dlb_redir_left_str, ft_lstnew(str));
	}
	g_info.redir_left = i;
	return (0);
}

void	createfile5(t_dlist *tmp, t_token *token)
{
	int	fd;

	while (tmp->next)
		tmp = tmp->next;
	token = tmp->content;
	fd = open((char *)token->value, O_TRUNC);
	g_info.redir_right = 1;
	close(fd);
}

int	createfileb(t_dlist *tmp, t_token *token, int i)
{
	if (token->type == 4)
		if (createfile3(tmp, token, i))
			return (1);
	if (token->type == 6)
		if (createfile4(tmp, token, i))
			return (1);
	if (token->type == 3)
		createfile5(tmp, token);
	if (token->type == 5)
		g_info.redir_right = 1;
	return (0);
}
