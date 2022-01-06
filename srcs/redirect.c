/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:34:01 by jessy             #+#    #+#             */
/*   Updated: 2021/11/17 20:20:25 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_redirect3b(t_dlist *tmp, t_token *token, t_dlist *mcmd)
{
	int		fdio;

	if (token->type == 4)
	{
		while (tmp->next)
			tmp = tmp->next;
		token = tmp->content;
		fdio = open((char *)token ->value, O_RDONLY);
		dup2(fdio, 0);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		token = tmp->content;
		fdio = open((char *)token->value, O_WRONLY | O_APPEND);
		dup2(fdio, 1);
	}
	if (mcmd)
		if (check_builtins(mcmd))
			check_exec(mcmd->content);
	close(fdio);
}

void	go_redirect3(t_dlist *tmp, t_dlist *rdrct,
	t_token *token, t_dlist *mcmd)
{
	int		fd[2];
	t_list	*dblrleft;

	tmp = rdrct->content;
	token = tmp->content;
	if (token->type == 6)
	{
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
	go_redirect3b(tmp, token, mcmd);
}

void	go_redirect(t_dlist *rdrct, t_dlist *mcmd)
{
	int		fdt[2];

	fdt[1] = dup(1);
	fdt[0] = dup(0);
	if (dlstsize(rdrct) == 2)
		go_redirect2(0, rdrct, 0, mcmd);
	else
		go_redirect3(0, rdrct, 0, mcmd);
	close(0);
	close(1);
	dup2(fdt[1], 1);
	dup2(fdt[0], 0);
	close(fdt[0]);
	close(fdt[1]);
	tmplstclear(&rdrct);
	ft_lstclear(&g_info.dlb_redir_left_str, &ft_memdel);
}

void	redirection2(t_dlist **stock_rdrct, t_dlist **stockcmd)
{
	if (createfile(*stock_rdrct))
	{
		tmplstclear(stock_rdrct);
		tmplstclear(stockcmd);
		return ;
	}
	go_redirect(clear_struct(stock_rdrct), *stockcmd);
	tmplstclear(stock_rdrct);
	tmplstclear(stockcmd);
}

void	redirection(void)
{
	t_dlist	*cmd;
	t_dlist	*stockcmd;
	t_gbc	*tmpgbc;
	t_dlist	*stock_rdrct;
	t_token	*token;

	stockcmd = 0;
	stock_rdrct = 0;
	if (!check_redirecterr(g_info.gbc))
	{
		tmpgbc = g_info.gbc;
		while (tmpgbc)
		{
			cmd = tmpgbc->str;
			token = cmd->content;
			if (token->type >= 3 && token->type <= 6)
				dlstadd_back(&stock_rdrct, dlstnew(cmd));
			else
				dlstadd_back(&stockcmd, dlstnew(cmd));
			tmpgbc = tmpgbc->next;
		}
		redirection2(&stock_rdrct, &stockcmd);
	}
}
