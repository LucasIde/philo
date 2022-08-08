/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 08:05:08 by lide              #+#    #+#             */
/*   Updated: 2022/08/08 11:54:17 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(int tot, pthread_mutex_t *mute)
{
	int	i;

	i = -1;
	while (++i < tot)
		pthread_mutex_init(&mute[i], NULL);
}

t_philo	value_copy(t_philo *value) //creer une struct pour stocker les adresses a free
{
	t_philo	new;

	new = *value;
	return (new);
}
