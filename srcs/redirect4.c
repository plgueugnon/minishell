/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:31:57 by jessy             #+#    #+#             */
/*   Updated: 2021/10/31 02:32:58 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	createfile(t_dlist *allfile)
{
	t_token		*token;
	t_dlist		*tmp;
	int			i;

	i = 1;
	while (allfile)
	{
		tmp = allfile->content;
		token = tmp->content;
		if (token->type != 4 && token->type != 6)
			if (createfile2(tmp, token))
				return (1);
		tmp = allfile->content;
		token = tmp->content;
		if (createfileb(tmp, token, i))
			return (1);
		i++;
		allfile = allfile->next;
	}
	return (0);
}

t_dlist	*clear_struct2(t_dlist **tmp, t_token **token,
	t_dlist **tmp2, t_dlist **lst)
{
	if (g_info.redir_right)
	{
		while (((*token)->type == 4 || (*token)->type == 6))
		{
			*lst = (*lst)->prev;
			(*tmp2) = (*lst)->content;
			(*token) = (*tmp2)->content;
		}
		dlstadd_back(tmp, dlstnew((*tmp2)));
	}
	while ((*lst)->prev)
		*lst = (*lst)->prev;
	return (*tmp);
}

t_dlist	*clear_struct(t_dlist **lst)
{
	int		i;
	t_dlist	*tmp;
	t_dlist	*tmp2;
	t_token	*token;

	i = 0;
	tmp = 0;
	if (g_info.redir_left)
	{
		while (++i < g_info.redir_left)
			*lst = (*lst)->next;
		tmp2 = (*lst)->content;
		dlstadd_back(&tmp, dlstnew(tmp2));
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	tmp2 = (*lst)->content;
	token = tmp2->content;
	return (clear_struct2(&tmp, &token, &tmp2, lst));
}

void	go_redirect2b(void)
{
	int		fd[2];
	t_list	*dblrleft;

	pipe(fd);
	dblrleft = g_info.dlb_redir_left_str;
	while (dblrleft->next)
	{
		ft_putstr_fd(dblrleft->content, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		dblrleft = dblrleft->next;
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

void	go_redirect2t(t_dlist *tmp, t_dlist *rdrct, t_token *token, int *fdio)
{
	while (tmp->next)
		tmp = tmp->next;
	token = tmp->content;
	if (rdrct->next)
		fdio[0] = open((char *)token->value, O_RDONLY);
	else
		fdio[1] = open((char *)token->value, O_WRONLY | O_APPEND);
}
