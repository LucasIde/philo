/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:36:13 by lide              #+#    #+#             */
/*   Updated: 2022/08/11 18:21:38 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	count(unsigned long n2)
{
	unsigned long	tmp;
	int				nb;

	tmp = n2;
	nb = 0;
	if (tmp < 0)
	{
		tmp *= -1;
		nb += 1;
	}
	while (tmp > 0)
	{
		tmp /= 10;
		nb++;
	}
	return (nb);
}

static char	*ft_itoa2(unsigned long n2, int nb)
{
	int		i;
	char	*a;

	i = 0;
	a = (char *)malloc(sizeof(char) * (++nb + 1));
	if (!a)
		return (NULL);
	if (n2 < 0)
	{
		i++;
		n2 *= -1;
		a[0] = '-';
	}
	a[nb--] = 0;
	a[nb] = ' ';
	while (nb > i)
	{
		a[nb - 1] = (n2 % 10) + '0';
		n2 /= 10;
		nb--;
	}
	return (a);
}

char	*ft_itoa(long n)
{
	int				nb;
	char			*a;
	unsigned long	n2;

	n2 = (unsigned long)n;
	if (n2 == 0)
	{
		a = (char *)malloc(sizeof(char) * 3);
		if (!a)
			return (NULL);
		a[0] = '0';
		a[1] = ' ';
		a[2] = '\0';
		return (a);
	}
	nb = count(n2);
	return (ft_itoa2(n2, nb));
}

int	ft_putnbr(long n)
{
	char	*nb;

	nb = ft_itoa(n);
	if (!nb)
		return (1);
	write(1, nb, len1(nb));
	free(nb);
	return (0);
}
