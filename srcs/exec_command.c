/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 01:09:41 by jessy             #+#    #+#             */
/*   Updated: 2021/11/17 11:51:32 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_dlist *mcmd)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = 0;
	if (g_info.path)
		return (1);
	if (!mcmd)
		joincmd(&cmd, (t_dlist *)g_info.gbc->str);
	else
		joincmd(&cmd, (t_dlist *)mcmd->content);
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (!ft_strncmp(cmd, "echo", i))
		echo(cmd, 1);
	else if (!ft_strncmp(cmd, "cd", i))
		cd(cmd);
	else if (!ft_strncmp(cmd, "pwd", i))
		pwd(cmd, 1);
	else
		return (check_builtins2(cmd, i));
	free(cmd);
	return (0);
}

char	**dup_env(t_list *env)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	if (!ret)
		return (0);
	while (env)
	{
		ret[i++] = ft_strdup((char *)env->content);
		env = env->next;
	}
	ret[i] = 0;
	return (ret);
}

void	check_exec2(char *tmp, char **str)
{
	signal(SIGINT, ft_sighandler);
	if ((tmp[0] == '.' && tmp[1] == '/') || tmp[0] == '/')
		execve(str[0], str, dup_env(g_info.env));
	else
		execve((char *)g_info.path->content,
			str, dup_env(g_info.env));
}

int	check_exec(t_dlist *mcmd)
{
	char	*tmp;
	char	**str;
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (!mcmd)
		joincmd(&tmp, (t_dlist *)g_info.gbc->str);
	else
		joincmd(&tmp, (t_dlist *)mcmd);
	pid = fork();
	str = ft_split(tmp, ' ');
	if (pid == -1)
		ft_exit(0, err_pid);
	else if (!pid)
		check_exec2(tmp, str);
	else
	{
		waitpid(pid, &errno, 0);
		signal(SIGINT, ft_sighandler);
	}
	free_dbl(str);
	if (g_info.stop)
		errno = 130;
	errno = errno % 255;
	return (free_ret(tmp, 0));
}

void	exec_command(t_dlist *list)
{
	t_dlist	*tmp5;
	t_token	*token;

	g_info.tmperrno = 0;
	if (!check_command(list))
	{
		tmp5 = g_info.gbc->str;
		token = tmp5->content;
		if (g_info.gbc->next || (token->type >= 3 && token->type <= 6))
			redirection();
		else if (check_builtins(0))
			check_exec(0);
	}
	g_info.tmperrno = errno;
	ft_lstclear(&g_info.path, &ft_memdel);
	gbcclear(&g_info.gbc);
}
