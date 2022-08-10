/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:52:58 by lide              #+#    #+#             */
/*   Updated: 2022/08/10 17:38:52 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_create(int verif ,char *str, pthread_t *philo, t_philo *value)
{
	int	i;

	i = -1;
	while (++i < value->tot)
		pthread_mutex_destroy(&value->mt[i]);
	pthread_mutex_destroy(value->wright);
	free(value->mt);
	free(value->wright);
	free(value->check);
	if (verif)
		free(philo);
	if (verif < 2)
		return (write_error(str));
	else
		return (0);
}
