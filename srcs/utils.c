/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 08:04:46 by lide              #+#    #+#             */
/*   Updated: 2022/08/11 15:53:09 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	len1(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	write_error(char *str)
{
	write(2, str, len1(str));
	return (1);
}

int	atoi2(char *str, int i, int x)
{
	long	j;
	long	tmp;

	j = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = j;
		j *= 10;
		j += str[i] - '0';
		if (tmp > j)
		{
			if (x == -1)
				return (0);
			if (x == 1)
				return (-1);
		}
		i++;
	}
	return (j * x);
}

int	ft_atoi(char *str)
{
	int		i;
	int		x;

	i = 0;
	x = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x = -1;
		i++;
	}
	return (atoi2(str, i, x));
}
