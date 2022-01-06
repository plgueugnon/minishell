/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:56:18 by pgueugno          #+#    #+#             */
/*   Updated: 2020/11/11 21:05:46 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char unsigned	value;
	char unsigned	*str;

	i = 0;
	value = c;
	str = b;
	while (i < len)
	{
		*str = value;
		str++;
		i++;
	}
	return (b);
}
