/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:36:20 by jessy             #+#    #+#             */
/*   Updated: 2021/11/08 21:30:41 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_end(t_dlist **alst)
{
	t_token	*token;
	t_dlist	*tmp1;
	t_dlist	*tmp2;

	tmp1 = *alst;
	if (!tmp1->next)
		return ;
	while (tmp1 && tmp1->next->next)
		tmp1 = tmp1->next;
	tmp2 = tmp1->next;
	token = tmp2->content;
	if (!ft_strcmp((char *)token->value, " "))
	{
		free(token->value);
		free(token);
		free(tmp2);
		tmp1->next = 0;
	}
}

void	fill_gbc2(int *i, int *check, t_dlist *tmp)
{
	t_token	*token;

	if (!tmp)
		return ;
	token = tmp->content;
	while (tmp && (!(token->type >= 3 && token->type <= 6)))
	{
		tmp = tmp->next;
		if (tmp)
			token = tmp->content;
		(*i)++;
		*check = 1;
	}
}

t_dlist	*fill_gbc(t_dlist *lst, int i)
{
	t_dlist	*tmp;
	t_dlist	*forgbc;
	int		check;

	tmp = lst;
	check = 0;
	if (!i)
		fill_gbc2(&i, &check, tmp);
	else
		check = 1;
	tmp = lst;
	forgbc = tmp;
	if (check)
	{
		while (i-- > 1)
			tmp = tmp->next;
		lst = tmp->next;
		tmp->next = 0;
		check_end((t_dlist **)&forgbc);
		lstaddback_gbc(&g_info.gbc, newgbc(TOKEN, -1, (void *)forgbc));
	}
	return (lst);
}

int	check_path2(char **path, char *tmp1)
{
	struct stat	sb;
	int			i;
	char		*checkpth;

	i = -1;
	while (path[++i])
	{
		checkpth = strpthjoin(path[i], tmp1);
		if (!stat(checkpth, &sb))
		{
			ft_lstadd_back(&g_info.path, ft_lstnew((void *)checkpth));
			return (0);
		}
		free(checkpth);
	}
	return (1);
}

int	check_path(char *tmp1)
{
	char		*env_path;
	char		**path;
	t_list		*tmp;

	tmp = g_info.env;
	while (tmp && ft_strncmp(tmp->content, "PATH=", 5))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tmp1, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		errno = 127;
		return (2);
	}
	env_path = tmp->content;
	path = ft_split(&env_path[5], ':');
	if (!check_path2(path, tmp1))
	{
		free_dbl(path);
		return (0);
	}
	free_dbl(path);
	return (1);
}
