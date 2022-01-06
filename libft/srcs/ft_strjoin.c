/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:56:51 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 14:58:19 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_rec(const char *s)
{
	if (*s == '\0')
		return (0);
	return (ft_strlen_rec(s + 1) + 1);
}

static char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		len1;
	int		len2;
	int		j;
	char	*dst;

	j = 0;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen_rec((char *)s1);
	len2 = ft_strlen_rec((char *)s2);
	len = len1 + len2;
	dst = malloc(sizeof(char) * len + 1);
	if (dst == NULL)
		return (0);
	dst = ft_strcpy(dst, (char *)s1);
	while (j < len2)
	{
		dst[len1 + j] = *s2;
		s2++;
		j++;
	}
	*(dst + (len)) = '\0';
	return (dst);
}
