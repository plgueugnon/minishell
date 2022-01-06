/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 01:00:24 by jessy             #+#    #+#             */
/*   Updated: 2021/10/29 18:12:41 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export1(int fd)
{
	t_list	*tmp;

	tmp = g_info.env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->content, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
}

void	export2(char *cmd, int i)
{
	int		j;
	int		add;
	char	*str;
	t_list	*tmp;

	add = 0;
	j = 0;
	tmp = g_info.env;
	export3(&i, &j, &add, cmd);
	str = supp_add(&cmd[i]);
	if (add)
		j--;
	while (tmp && ft_strncmp(tmp->content, str, j))
		tmp = tmp->next;
	if (!tmp)
		ft_lstadd_back(&g_info.env, ft_lstnew(str));
	else
	{
		free(str);
		if (add)
			export4(tmp, cmd, i, j);
		else
			export5(tmp, cmd, i);
	}
	errno = 0;
}

void	export3(int *i, int *j, int *add, char *cmd)
{
	while (cmd[*i + *j] && cmd[*i + *j] != '=')
	{
		if (cmd[*i + *j] == '+' && cmd[*i + *j + 1] == '=')
			(*add)++;
		else if (!ft_isalnum(cmd[*i + *j]) && cmd[*i + *j] != '_')
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(&cmd[*i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			errno = 1;
			return ;
		}
		(*j)++;
	}
	if (cmd[*i + *j] != '=')
	{
		errno = 0;
		return ;
	}
}

void	export4(t_list	*tmp, char *cmd, int i, int j)
{
	char	*str;

	str = ft_strjoin(tmp->content, &cmd[i + j + 2]);
	free(tmp->content);
	tmp->content = str;
}

void	export5(t_list	*tmp, char *cmd, int i)
{
	free(tmp->content);
	tmp->content = ft_strdup(&cmd[i]);
}
