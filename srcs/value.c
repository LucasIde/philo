/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:27:10 by lide              #+#    #+#             */
/*   Updated: 2022/08/08 11:04:06 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	change_type(int argc, char **argv, t_philo *value)
{
	value->tot = atoi(argv[0]);
	value->die = atoi(argv[1]);
	value->eat = atoi(argv[2]);
	value->sleep = atoi(argv[3]);
	if(argc < 5)
		value->nb_eat = -1;
	else
		value->nb_eat = atoi(argv[4]);
	value->nb = 0;
	if((argc == 5 && value->nb_eat < 0) || value->tot < 0
		|| value->die < 0 || value->eat < 0 || value->sleep < 0)
		return (write_error("eating minus time ?"));
	return (0);
}

int	check_value(int argc, char **argv, t_philo **value)
{
	int	i;
	int	j;

	i = -1;
	while (++i < argc)
	{
		j = -1;
		while(argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (write_error("only digits are accepted"));
	}
	if (change_type(argc, argv, value))
		return (1);

	return (0);
}
