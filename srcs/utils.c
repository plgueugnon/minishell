/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:46:08 by jessy             #+#    #+#             */
/*   Updated: 2021/11/01 15:35:53 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tmplstclear(t_dlist **lst)
{
	t_dlist	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
	free(*lst);
	*lst = 0;
}

void	init_var(void)
{
	g_info.dlb_redir_left_str = 0;
	g_info.redir_left = 0;
	g_info.redir_right = 0;
	g_info.child = 0;
	g_info.gnl = 0;
	g_info.stop = 0;
}

size_t	ft_strlen_utils(const char *s, char stop)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == stop)
			return (i);
		i++;
	}
	return (i);
}

void	ft_get_env(char **envp)
{
	int		i;
	char	*str;
	t_list	*new;

	i = 0;
	g_info.env = NULL;
	g_info.cmd = NULL;
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		new = ft_lstnew(str);
		ft_lstadd_back(&g_info.env, new);
		i++;
	}
}

void	init_tab_token(void)
{
	g_info.tab_token[0].value = ft_strdup("|");
	g_info.tab_token[0].type = pipeline;
	g_info.tab_token[1].value = ft_strdup("$");
	g_info.tab_token[1].type = dollar;
	g_info.tab_token[2].value = ft_strdup(" ");
	g_info.tab_token[2].type = space;
	g_info.tab_token[3].value = ft_strdup(">");
	g_info.tab_token[3].type = redir_right;
	g_info.tab_token[4].value = ft_strdup("<");
	g_info.tab_token[4].type = redir_left;
	g_info.tab_token[5].value = ft_strdup(">>");
	g_info.tab_token[5].type = dble_redir_right;
	g_info.tab_token[6].value = ft_strdup("<<");
	g_info.tab_token[6].type = dble_redir_left;
	g_info.tab_token[7].value = ft_strdup("\'");
	g_info.tab_token[7].type = sgle_quote;
	g_info.tab_token[8].value = ft_strdup("\"");
	g_info.tab_token[8].type = dble_quote;
	g_info.tab_token[9].value = ft_strdup("?");
	g_info.tab_token[9].type = errno_call;
	g_info.tab_token[10].value = 0;
	g_info.tab_token[10].type = 0;
}
