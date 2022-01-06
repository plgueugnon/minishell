/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 01:02:06 by jessy             #+#    #+#             */
/*   Updated: 2021/11/08 17:42:23 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *cmd, int fd)
{
	int	i;

	i = 6;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (!cmd[i])
		export1(fd);
	else
		export2(cmd, i);
}

void	cd3(void)
{
	char	*str;
	t_list	*tmp;

	tmp = g_info.env;
	str = 0;
	str = getcwd(str, 1000);
	while (tmp && ft_strncmp(tmp->content, "PWD=", 4))
		tmp = tmp->next;
	if (!tmp)
		ft_lstadd_back(&g_info.env, ft_lstnew(ft_strjoin("PWD=", str)));
	free(str);
}
