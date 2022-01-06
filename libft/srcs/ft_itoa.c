/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:04:29 by pgueugno          #+#    #+#             */
/*   Updated: 2021/06/08 14:55:39 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(int n, int s)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	if (s < 0)
		i++;
	return (i);
}

static void	ft_fill_str(char *str, int n, int s, int size)
{
	str[size] = '\0';
	size--;
	while (n >= 10)
	{
		str[size] = (n % 10) + 48;
		size--;
		n /= 10;
	}
	while (n < 10 && size >= 0)
	{
		str[size] = (n % 10) + 48;
		size--;
	}
	if (s < 0)
		str[0] = '-';
}

static char	*ft_cpy_str(char *s, int start, int len)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (0);
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		s;
	int		size;
	char	*s_intmin;

	s_intmin = "-2147483648";
	if (n < -2147483647)
		return (ft_cpy_str(s_intmin, 0, 12));
	if (n < 0)
		s = -1;
	else
		s = 1;
	if (s < 0)
		n *= -1;
	size = ft_num_len(n, s);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	ft_fill_str(str, n, s, size);
	return (str);
}
