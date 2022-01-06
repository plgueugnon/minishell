/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:33:40 by jessy             #+#    #+#             */
/*   Updated: 2021/11/17 18:28:43 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_redirect_msg(t_token	*token)
{
	ft_putstr_fd("bash:", 2);
	ft_putstr_fd((char *)token->value, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	errno = 1;
}

void	go_redirect2(t_dlist *tmp, t_dlist *rdrct,
	t_token *token, t_dlist *mcmd)
{
	int		fdio[2];

	fdio[0] = -1;
	fdio[1] = -1;
	while (rdrct)
	{
		tmp = rdrct->content;
		token = tmp->content;
		if (token->type == 6)
			go_redirect2b();
		else
			go_redirect2t(tmp, rdrct, token, fdio);
		rdrct = rdrct->next;
	}
	if (fdio[0] >= 0)
		dup2(fdio[0], 0);
	if (fdio[1] >= 0)
		dup2(fdio[1], 1);
	if (check_builtins(mcmd))
		check_exec(mcmd->content);
	close(fdio[0]);
	close(fdio[1]);
}
