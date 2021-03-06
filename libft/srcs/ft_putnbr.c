/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:31:50 by pgueugno          #+#    #+#             */
/*   Updated: 2021/01/25 10:33:36 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long int n)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n < 10)
	{
		n += 48;
		write(1, &n, 1);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		n = (n % 10) + 48;
		write(1, &n, 1);
	}
}
