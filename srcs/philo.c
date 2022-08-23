/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:53 by lide              #+#    #+#             */
/*   Updated: 2022/08/23 16:16:10 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_action(t_philo *value, int verif)
{
	long	time;

	pthread_mutex_lock(value->wright);
	if (*value->check == 0)
	{
		time = get_time() - value->time;
		if (verif == 1)
			printf("%ld "FORK, time, value->nb + 1);
		if (verif == 2)
			printf("%ld "EAT, time, value->nb + 1);
		if (verif == 3)
			printf("%ld "SLEEP, time, value->nb + 1);
		if (verif == 4)
			printf("%ld "THINK, time, value->nb + 1);
		if (verif == 5 && *value->check == 0)
		{
			change_check(value);
			printf("%ld "DIE, time, value->nb + 1);
		}
	}
	pthread_mutex_unlock(value->wright);
	return (0);
}

void	routine(t_philo *value, int j)
{
	while (!(*value->check) && value->nb_eat != 0 && value->tot > 1)
	{
		pthread_mutex_lock(&value->mt[value->nb]);
		pthread_mutex_lock(&value->mt[j]);
		print_action(value, 1);
		print_action(value, 1);
		*value->eat = 1;
		print_action(value, 2);
		ft_wait(value->t_eat, value, 1);
		pthread_mutex_unlock(&value->mt[value->nb]);
		pthread_mutex_unlock(&value->mt[j]);
		print_action(value, 3);
		ft_wait(value->sleep, value, 0);
		print_action(value, 4);
	}
}

void	life(t_philo *value)
{
	pthread_t	death[1];
	int			eat;
	int			j;

	eat = 0;
	value->eat = &eat;
	if (*value->check == 0)
	{
		if (pthread_create(&death[0], NULL, (void *)death_timer, (void *)value))
		{
			change_check(value);
			printf("Error: pthread_create\n");
		}
	}
	if (value->nb == 0)
		j = value->tot - 1;
	else
		j = value->nb - 1;
	if (value->nb % 2 != 0)
		usleep(50);
	routine(value, j);
	pthread_join(death[0], NULL);
	free(value);
}

int	create_philo(t_philo *value)
{
	pthread_t	*philo;
	t_philo		*new;
	int			i;

	if (init_mutex(value->tot, value))
		return (free_value(value, "Error: malloc mutex\n"));
	philo = init_philo(value->tot);
	if (!philo)
		return (free_create(0, "Error: malloc philo\n", philo, value));
	i = -1;
	while (++i < value->tot)
	{
		new = value_copy(value, i);
		if (!new)
			return (error_value(value, i, philo));
		if (pthread_create(&philo[i], NULL, (void *)&life, (void *)new))
			return (free_create(1, "Error: pthread_create\n", philo, value));
	}
	i = -1;
	while (++i < value->tot)
		if (pthread_join(philo[i], NULL))
			return (free_create(1, "Error: pthread_join\n", philo, value));
	return (free_create(2, NULL, philo, value));
}

int	main(int argc, char **argv)
{
	t_philo	value;

	if (argc < 5)
		return (write_error("not enough arguments\n"));
	else if (argc > 6)
		return (write_error("too much arguments\n"));
	if (check_value(argc, argv, &value))
		return (1);
	if (value.nb_eat == 0)
	{
		free(value.check);
		free(value.end);
		return (0);
	}
	if (create_philo(&value))
		return (1);
	return (0);
}
