/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 23:21:52 by jessy             #+#    #+#             */
/*   Updated: 2021/11/08 22:06:17 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_code(t_err_code err_code)
{
	if (err_code == 1)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("Error : Malloc failed\n", 2);
		return (1);
	}
	if (err_code == 2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("Error : fork failed\n", 2);
		return (1);
	}
	if (err_code == 3)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("Error : open failed\n", 2);
		return (1);
	}
	return (0);
}

int	exit2bis(char *cmd, int *i, int j)
{
	int	nbspace;

	nbspace = 0;
	if (cmd[*i] == '-')
		j++;
	while (cmd[*i + ++j])
	{
		if (cmd[*i + j] == ' ' && cmd[*i + j + 1] != ' ' && cmd[*i + j + 1])
		{
			nbspace++;
			while (cmd[*i + j] == ' ')
				j++;
		}
	}
	return (nbspace);
}

int	exit2(char *cmd, int *i, int j)
{
	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
	if (!cmd[*i])
	{
		clear_cmd_lst(&g_info.cmd);
		ft_lstclear(&g_info.env, &ft_memdel);
		if (!g_info.child)
			ft_putstr_fd("exit\n", 1);
		free(cmd);
		exit(errno);
	}
	return (exit2bis(cmd, i, j));
}

void	exit3(char *cmd, int i)
{
	int	error;

	error = 0;
	errno = ft_atoll(&cmd[i], &error);
	if (errno < 0)
		errno += 256;
	errno %= 256;
	if (!g_info.child)
		ft_putstr_fd("exit\n", 1);
	if (error)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(&cmd[i], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		errno = 2;
	}
}

void	ft_exit(char *cmd, t_err_code err_code)
{
	int	i;

	i = 4;
	if (cmd)
	{
		if (exit2(cmd, &i, -1))
		{
			errno = 1;
			ft_putstr_fd("exit: too many arguments\n", 2);
			return ;
		}
		exit3(cmd, i);
		free(cmd);
	}
	if (error_code(err_code))
		errno = 1;
	ft_lstclear(&g_info.env, &ft_memdel);
	if (!g_info.child && !cmd)
		write(1, "exit\n", 5);
	exit(errno);
}
