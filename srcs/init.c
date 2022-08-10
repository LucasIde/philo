/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 08:05:08 by lide              #+#    #+#             */
/*   Updated: 2022/08/10 17:40:41 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_t *init_philo(int tot)
{
	pthread_t	*th;

	th = (pthread_t *)malloc(sizeof(pthread_t) * tot);
	if (!th)
		return (NULL);
	return (th);
}

int	init_mutex(int tot, t_philo *value)
{
	pthread_mutex_t	*mt;
	pthread_mutex_t	*wright;
	int	i;

	wright = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!wright)
		return(1);
	mt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * tot);
	if (!mt)
	{
		free(wright);
		return(1);
	}
	i = -1;
	while (++i < tot)
		pthread_mutex_init(&mt[i], NULL);
	pthread_mutex_init(wright, NULL);
	value->mt = mt;
	value->wright = wright;
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

int	error_value(t_philo *value, int i, pthread_t *philo)
{
	int	j;

	*value->check = 1;
	j = -1;
	while (++j < i)
		if (pthread_join(philo[j], NULL))
			return (free_create(1, "Error: pthread_join\n", philo, value));
	return (free_create(1, "Error: malloc value_copy\n", philo, value));
}
