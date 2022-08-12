/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 08:05:08 by lide              #+#    #+#             */
/*   Updated: 2022/08/12 19:03:48 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_t	*init_philo(int tot)
{
	pthread_t	*th;

	th = (pthread_t *)malloc(sizeof(pthread_t) * tot);
	if (!th)
		return (NULL);
	return (th);
}

int	free_error_mutex(pthread_mutex_t *wright, pthread_mutex_t *wait, int verif)
{
	free(wright);
	if (verif == 1)
		free(wait);
	return (1);
}

int	init_mutex(int tot, t_philo *value)
{
	pthread_mutex_t	*mt;
	pthread_mutex_t	*wright;
	pthread_mutex_t	*wait;
	int				i;

	wright = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!wright)
		return (1);
	wait = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!wait)
		return (free_error_mutex(wright, wait, 0));
	mt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * tot);
	if (!mt)
		return (free_error_mutex(wright, wait, 1));
	i = -1;
	while (++i < tot)
		pthread_mutex_init(&mt[i], NULL);
	pthread_mutex_init(wright, NULL);
	pthread_mutex_init(wait, NULL);
	value->mt = mt;
	value->wright = wright;
	value->wait = wait;
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
