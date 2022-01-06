/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:55:54 by pgueugno          #+#    #+#             */
/*   Updated: 2020/11/11 21:03:39 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*c_dst;
	unsigned const char	*c_src;
	size_t				i;

	c_dst = dst;
	c_src = src;
	i = 0;
	if (c_dst == NULL && c_src == NULL)
		return (NULL);
	while (i < n)
	{
		*c_dst = *c_src;
		c_src++;
		c_dst++;
		i++;
	}
	return (dst);
}
