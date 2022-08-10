/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:27:10 by lide              #+#    #+#             */
/*   Updated: 2022/08/10 17:58:14 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	change_type(int argc, char **argv, t_philo *value)
{
	int	*check;

	check = (int *)malloc(sizeof(int));
	if (!check)
		return (write_error("error malloc check\n"));
	*check = 0;
	value->check = check;
	value->tot = atoi(argv[1]);
	value->die = atoi(argv[2]);
	value->t_eat = atoi(argv[3]);
	value->sleep = atoi(argv[4]);
	if(argc < 6)
		value->nb_eat = -1;
	else
		value->nb_eat = atoi(argv[5]);
	value->nb = 0;
	if((argc == 6 && value->nb_eat < 0) || value->tot < 1
		|| value->die < 0 || value->eat < 0 || value->sleep < 0)
	{
		free(check);
		return (write_error("eating minus time ?\n"));// trouver autre chose
	}
	return (0);
}

int	check_value(int argc, char **argv, t_philo *value)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while(argv[i][++j])
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (write_error("only digits are accepted\n"));
	}
	if (change_type(argc, argv, value))
		return (1);

	return (0);
}
