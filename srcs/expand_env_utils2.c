/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:02:20 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/12 18:45:47 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_value_in_env(char *envval, char *cmdval)
{
	size_t	e;
	size_t	c;

	e = ft_strlen_utils(envval, '=');
	c = ft_strlen(cmdval);
	if (!ft_strncmp(envval, cmdval, e) && e == c)
		return (1);
	return (0);
}

char	**get_val_to_expand(t_token	*token)
{
	int		i;
	char	**tab;
	char	*str;

	i = 0;
	str = token->value;
	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (0);
	while (str[i] && valid_env_char(str[i]))
		i++;
	tab[0] = ft_strndup(str, i);
	tab[1] = ft_strndup(str + i, (ft_strlen(str) - i));
	return (tab);
}

int	clean_tab(char **tab, int ret)
{
	free(tab[0]);
	free(tab[1]);
	free(tab);
	return (ret);
}

static int	clean_n_go(char **tab, t_dlist **iter, t_dlist **tmp)
{
	clear_cmd_node(tmp);
	clear_cmd_node(iter);
	return (clean_tab(tab, 0));
}

int	find_env_var(t_dlist **iter)
{
	t_dlist	*tmp;
	t_list	*env;
	char	**tab;
	char	*str;

	tmp = *iter;
	*iter = (*iter)->next;
	tab = get_val_to_expand((*iter)->content);
	if (g_info.env)
	{
		env = g_info.env;
		while (env)
		{
			if (check_if_value_in_env(env->content, tab[0]))
			{
				str = ft_strjoin(env->content, tab[1]);
				replace_node_value(&str, iter);
				clear_cmd_node(&tmp);
				reparse_expanded_value(iter);
				return (clean_tab(tab, 1));
			}
			env = env->next;
		}
	}
	return (clean_n_go(tab, iter, &tmp));
}
