/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:58:44 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 15:00:32 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*dst;

	i = 0;
	if (!s)
		return (0);
	if ((int)start >= s_len(s))
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
