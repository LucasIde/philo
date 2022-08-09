/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:52:58 by lide              #+#    #+#             */
/*   Updated: 2022/08/09 18:39:41 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_create(int verif ,char *str, pthread_t *philo, t_philo *value)
{
	free(value->mt);
	free(value->wright);
	if (verif)
		free(philo);
	return (write_error(str));
}
