/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:52:58 by lide              #+#    #+#             */
/*   Updated: 2022/08/23 16:39:22 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_value(t_philo *value, char *str)
{
	free(value->check);
	free(value->end);
	return (write_error(str));
}

int	free_create(int verif, char *str, pthread_t *philo, t_philo *value)
{
	int	i;

	i = -1;
	while (++i < value->tot)
		pthread_mutex_destroy(&value->mt[i]);
	pthread_mutex_destroy(value->wright);
	pthread_mutex_destroy(value->wait);
	pthread_mutex_destroy(value->dead);
	free(value->mt);
	free(value->wright);
	free(value->wait);
	free(value->dead);
	free(value->check);
	free(value->end);
	if (verif)
		free(philo);
	if (verif < 2)
		return (write_error(str));
	else
		return (0);
}

int	error_value(t_philo *value, int i, pthread_t *philo)
{
	int	j;

	change_check(value);
	j = -1;
	while (++j < i)
		if (pthread_join(philo[j], NULL))
			return (free_create(1, "Error: pthread_join\n", philo, value));
	return (free_create(1, "Error: malloc value_copy\n", philo, value));
}

int	free_error_mutex(pthread_mutex_t *wright, pthread_mutex_t *wait,
	pthread_mutex_t *mt, int verif)
{
	free(wright);
	if (verif > 0)
		free(wait);
	if (verif == 2)
		free(mt);
	return (1);
}
