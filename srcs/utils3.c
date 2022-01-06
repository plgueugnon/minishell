/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 02:56:42 by jessy             #+#    #+#             */
/*   Updated: 2021/11/10 17:15:03 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_sign_polarity(int *s, int *i)
{
	*s *= -1;
	(*i)++;
}

long long int	ft_atoll(char *str, int *error)
{
	int						i;
	int						s;
	long long int			r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-')
		change_sign_polarity(&s, &i);
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	if (r < 0 || str[i] || ft_strlen(str) > 20)
	{
		*error = 1;
		return (2);
	}
	return (r * s);
}

char	*supp_add(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '+')
		i++;
	if (str[i] == '+')
	{
		if (ft_go_malloc(&ret, (sizeof(char) + ft_strlen(str))))
			ft_exit(0, err_malloc);
		i = 0;
		while (str[i])
		{
			if (str[i] != '+')
				ret[j++] = str[i];
			i++;
		}
		ret[j] = 0;
		return (ret);
	}
	return (ft_strdup(str));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	return (1);
}

int	createfilestop(char *str)
{
	ft_lstclear(&g_info.dlb_redir_left_str, &ft_memdel);
	free(str);
	errno = 130;
	return (1);
}
