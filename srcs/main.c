/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 18:08:59 by jessy             #+#    #+#             */
/*   Updated: 2021/11/02 15:55:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	g_info;

char	**duplst(t_list *env)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!ret)
		ft_exit(0, err_malloc);
	while (env)
	{
		ret[i++] = ft_strdup(env->content);
		env = env->next;
	}
	ret[i] = 0;
	return (ret);
}

void	init_struct(void)
{
	g_info.pwd = 0;
	g_info.gbc = 0;
	g_info.path = 0;
	g_info.cmd = 0;
	g_info.nbpipe = 0;
	g_info.cmdpipe = 0;
	g_info.gnl = 0;
	init_tab_token();
	errno = 0;
	g_info.evrm = duplst(g_info.env);
}

void	change_shlv(t_list **env)
{
	t_list	*tmp;
	char	*str;
	int		i;
	char	*tmpstr;

	tmp = *env;
	while (tmp && ft_strncmp(tmp->content, "SHLVL", 5))
		tmp = tmp->next;
	str = tmp->content;
	i = ft_atoi(&str[6]) + 1;
	free(tmp->content);
	tmpstr = ft_itoa(i);
	tmp->content = ft_strjoin("SHLVL=", tmpstr);
	free(tmpstr);
}

char	**fill_nullenv(void)
{
	char	**ret;
	char	*pwd;
	char	*pth;
	int		i;

	i = 13;
	while (!pwd)
		pwd = getcwd(pwd, i++);
	ret = malloc(sizeof(char *) * 8);
	i = 0;
	if (!ret)
		ft_exit(0, err_malloc);
	pth = ft_strjoin("PATH=/usr/local/sbin:/usr/local/bin:/usr",
			"/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	ret[i++] = ft_strdup("LS_COLORS=");
	ret[i++] = ft_strdup("LESSCLOSE=/usr/bin/lesspipe %s %s");
	ret[i++] = ft_strjoin("PWD=", pwd);
	ret[i++] = pth;
	ret[i++] = ft_strdup("SHLVL=0");
	ret[i++] = ft_strdup("LESSOPEN=| /usr/bin/lesspipe %s");
	ret[i++] = ft_strdup("_=/usr/bin/env");
	ret[i] = 0;
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (!envp[0])
		envp = fill_nullenv();
	ft_get_env(envp);
	change_shlv(&g_info.env);
	init_struct();
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
	ft_prompt();
	ft_exit(0, no_err);
	return (0);
}
