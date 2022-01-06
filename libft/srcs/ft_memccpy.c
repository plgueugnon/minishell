/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:55:24 by pgueugno          #+#    #+#             */
/*   Updated: 2020/11/11 21:00:30 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*c_dst;
	unsigned const char	*c_src;
	unsigned char		k;
	size_t				i;

	i = 0;
	c_dst = dst;
	c_src = src;
	k = c;
	if (*c_src == '\0')
		return (NULL);
	if (*c_src != '\0')
	{
		while (i < n)
		{
			*c_dst = *c_src;
			if (*c_src == k)
				return (c_dst + 1);
			c_src++;
			c_dst++;
			i++;
		}
	}
	return (NULL);
}
