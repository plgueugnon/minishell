/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:58:04 by pgueugno          #+#    #+#             */
/*   Updated: 2021/11/07 20:54:56 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	a;
	int		i;

	str = (char *)s;
	a = c;
	i = 0;
	if (!s)
		return (0);
	while (str[i])
		i++;
	while (i > 0)
	{
		if (str[i] == a)
			return (&str[i]);
		i--;
	}
	if (str[i] == a)
		return (&str[i]);
	return (0);
}
