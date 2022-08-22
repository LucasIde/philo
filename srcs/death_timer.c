/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:00:24 by lide              #+#    #+#             */
/*   Updated: 2022/08/22 17:56:11 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_eat(t_philo *value)
{
	if (value->nb_eat > 0)//changement pour 0 dans le nbr de eat
		value->nb_eat -= 1;
	pthread_mutex_lock(value->wait);
	if (value->nb_eat == 0)
		*value->end -= 1;
	if (*value->end == 0)
		change_check(value);
	pthread_mutex_unlock(value->wait);
}

void	ft_wait(int time_to_wait, t_philo *value, int verif)
{
	long	time;
	long	new_time;

	time = get_time();
	new_time = get_time();
	if (verif && value->nb_eat > 0)
		check_eat(value);
	while (new_time - time < time_to_wait)
	{
		usleep(100);
		new_time = get_time();
	}
}

void	death_timer(t_philo *value)
{
	struct timeval	time;
	struct timeval	new_time;
	long			timer;

	gettimeofday(&time, NULL);
	while (*value->check == 0 && *value->end > 0)
	{
		usleep(5);
		gettimeofday(&new_time, NULL);
		timer = (new_time.tv_sec - time.tv_sec) * 1000;
		timer += (new_time.tv_usec - time.tv_usec) / 1000;
		if (timer >= value->die && *value->check == 0)
		{
			print_action(value, 5);
		}
		if (*value->eat == 1 && *value->check == 0)
		{
			gettimeofday(&time, NULL);
			*value->eat = 0;
		}
	}
}
