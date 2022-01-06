/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:39:06 by jessy             #+#    #+#             */
/*   Updated: 2021/11/10 11:31:23 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exist(char *str)
{
	struct stat	sb;

	if (stat(str, &sb))
		return (1);
	return (0);
}

int	check_binaire(char *str)
{
	int		fd;
	char	s[5];

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (1);
	read(fd, &s[0], 4);
	s[4] = '\0';
	if (!ft_strcmp(&s[1], "ELF"))
		return (close(fd));
	return (close(fd) + 1);
}

void	check_command4(t_dlist **dlsttmp1, int i)
{
	t_token	*token2;
	t_dlist	*dlsttmp2;

	token2 = (*dlsttmp1)->next->content;
	dlsttmp2 = (*dlsttmp1)->next;
	while (dlsttmp2 && token2->type != 9)
	{
		dlsttmp2 = dlsttmp2->next;
		if (dlsttmp2)
		{
			token2 = dlsttmp2->content;
			i++;
		}
	}
	dlsttmp2 = dlsttmp2->next;
	if (dlsttmp2)
		token2 = dlsttmp2->content;
	while (dlsttmp2 && token2->type == space)
	{
		i++;
		dlsttmp2 = dlsttmp2->next;
		if (dlsttmp2)
			token2 = dlsttmp2->content;
	}
	(*dlsttmp1) = fill_gbc((*dlsttmp1), i);
}

int	check_command6(char *chrtmp1, t_dlist **dlsttmp1)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(chrtmp1, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	clear_cmd_lst(dlsttmp1);
	errno = 126;
	return (1);
}

int	check_command7(char	*chrtmp1)
{
	ft_putstr_fd(chrtmp1, 2);
	ft_putstr_fd(": command not found\n", 2);
	clear_cmd_lst(&g_info.cmd);
	errno = 127;
	return (1);
}
