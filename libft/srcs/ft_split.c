/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:52:33 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 14:57:55 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_sep(const char src, char sep)
{
	if (src == sep)
		return (1);
	return (0);
}

static int	ft_count_lines(const char *s, char c)
{
	int	l;
	int	i;

	l = 1;
	i = 0;
	while (s[i])
	{
		if (ft_check_sep(s[i], c) == 0)
		{
			l++;
			while (s[i] && ft_check_sep(s[i], c) == 0)
				i++;
		}
		if (s[i])
			i++;
	}
	return (l);
}

static void	ft_strcpy(char *answer, char *f, const char *s)
{
	while (f < (char *)s)
		*(answer++) = *(f++);
	*answer = '\0';
}

static int	ft_fill_it(char const *s, char **answer, char c)
{
	char	*f;
	int		k;

	k = 0;
	while (*s)
	{
		if (ft_check_sep(*s, c) == 0)
		{
			f = (char *)s;
			while (*s && ft_check_sep(*s, c) == 0)
				s++;
			answer[k] = malloc(sizeof(char) * ((char *)s - f + 1));
			if (answer == NULL)
				return (0);
			ft_strcpy(answer[k++], f, s);
		}
		if (*s != '\0')
			s++;
	}
	answer[k] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**answer;

	if (!s)
		return (0);
	answer = malloc(sizeof(char *) * ((ft_count_lines(s, c) + 1)));
	if (answer == NULL)
		return (0);
	if (!ft_fill_it(s, answer, c))
		return (0);
	return (answer);
}
