/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dble_redir_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:01:47 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/10 00:57:09 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_multiple_str(char **split, char *last)
{
	int		i;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	if (!split || !split[i])
		return (0);
	tmp2 = ft_strdup(split[i]);
	tmp3 = tmp2;
	i++;
	while (split[i])
	{
		tmp3 = ft_strjoin(tmp2, split[i]);
		free(tmp2);
		tmp2 = tmp3;
		i++;
	}
	if (last)
	{
		tmp3 = ft_strjoin(tmp2, last);
		free(tmp2);
		tmp2 = tmp3;
	}
	return (tmp3);
}

char	**inputval_to_expand(char *str)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (0);
	while (str[i] && valid_env_char(str[i]))
		i++;
	tab[0] = ft_strndup(str, i);
	tab[1] = ft_strndup(str + i, (ft_strlen(str) - i));
	return (tab);
}

int	expand_input_env(char **s)
{
	char	**tab;
	char	*tmp;
	t_list	*env;

	tmp = *s;
	tab = inputval_to_expand(*s);
	if (g_info.env)
	{
		env = g_info.env;
		while (env)
		{
			if (check_if_value_in_env(env->content, tab[0]))
			{
				*s = ft_strjoin(env->content
						+ (ft_strlen_utils(env->content, '=') + 1), tab[1]);
				free(tmp);
				return (clean_tab(tab, 1));
			}
			env = env->next;
		}
		*s = ft_strdup("");
		free(tmp);
	}
	return (clean_tab(tab, 0));
}

void	expand_input_errno(char **split)
{
	char	*stmp;
	char	*errvalue;

	stmp = *split;
	errvalue = ft_itoa(errno);
	*split = ft_strjoin(errvalue, stmp + 1);
	free(errvalue);
	free(stmp);
}

void	expand_dlb_left_input(char **str)
{
	char	**split;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = ft_strlen(*str);
	if (!ft_strncmp(*str + (i - 1), "$", 1))
		tmp = "$";
	split = ft_split(*str, '$');
	i = 0;
	if (*str[0] != '$')
		i++;
	while (split[i])
	{
		if (*split[i] == '?')
			expand_input_errno(&split[i]);
		else
			expand_input_env(&split[i]);
		i++;
	}
	free(*str);
	*str = concat_multiple_str(split, tmp);
	clean_split(split);
}
