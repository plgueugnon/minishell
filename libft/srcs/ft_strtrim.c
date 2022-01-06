/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:58:19 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 14:59:08 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_rec(char const *s)
{
	if (*s == '\0')
		return (0);
	return (ft_strlen_rec(s + 1) + 1);
}

static char	*ft_str_chr(const char *s, int c)
{
	char	*str;
	char	a;
	int		i;

	str = (char *)s;
	a = c;
	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return (&str[i]);
		i++;
	}
	if (str[i] == a)
		return (&str[i]);
	return (0);
}

static char	*ft_sub_str(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if ((int)start >= ft_strlen_rec(s))
	{
		dst = malloc(sizeof(char) * 1);
		if (dst == NULL)
			return (0);
		dst[0] = '\0';
		return (dst);
	}
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (0);
	while ((size_t)i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*dst;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_str_chr(set, *s1))
		s1++;
	len = ft_strlen_rec(s1);
	while (len && ft_str_chr(set, s1[len]))
		len--;
	dst = ft_sub_str(s1, 0, len + 1);
	return (dst);
}
