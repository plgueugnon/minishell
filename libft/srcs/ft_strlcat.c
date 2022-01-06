/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:57:09 by pgueugno          #+#    #+#             */
/*   Updated: 2021/01/06 15:59:06 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (dstsize != 0)
	{
		while (dst[i] && i < dstsize)
			i++;
		j = 0;
		while (src[j] && j + i < dstsize - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
		if (j + i < dstsize)
			dst[j + i] = '\0';
	}
	k = 0;
	while (src[k] != '\0')
		k++;
	return (k + i);
}
