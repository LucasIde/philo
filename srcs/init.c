/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 08:05:08 by lide              #+#    #+#             */
/*   Updated: 2022/08/23 16:34:35 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	change_check(t_philo *value)
{
	pthread_mutex_lock(value->dead);
	*value->check = 1;
	pthread_mutex_unlock(value->dead);
}

pthread_t	*init_philo(int tot)
{
	pthread_t	*th;

	th = (pthread_t *)malloc(sizeof(pthread_t) * tot);
	if (!th)
		return (NULL);
	return (th);
}

void	init_all(int tot, t_philo *value)
{
	int	i;

	i = -1;
	while (++i < tot)
		pthread_mutex_init(&value->mt[i], NULL);
	pthread_mutex_init(value->wright, NULL);
	pthread_mutex_init(value->wait, NULL);
	pthread_mutex_init(value->dead, NULL);
}

int	init_mutex(int tot, t_philo *value)
{
	pthread_mutex_t	*mt;
	pthread_mutex_t	*wright;
	pthread_mutex_t	*wait;
	pthread_mutex_t	*dead;

	mt = NULL;
	wright = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!wright)
		return (1);
	wait = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!wait)
		return (free_error_mutex(wright, wait, mt, 0));
	mt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * tot);
	if (!mt)
		return (free_error_mutex(wright, wait, mt, 1));
	dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!dead)
		return (free_error_mutex(wright, wait, mt, 2));
	value->mt = mt;
	value->wright = wright;
	value->wait = wait;
	value->dead = dead;
	init_all(tot, value);
	return (0);
}

t_philo	*value_copy(t_philo *value, int i)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	*new = *value;
	new->nb = i;
	return (new);
}
