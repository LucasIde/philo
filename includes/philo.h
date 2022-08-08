/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:29:30 by lide              #+#    #+#             */
/*   Updated: 2022/08/08 11:46:15 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int	tot;
	int	die;
	int	eat;
	int	sleep;
	int nb_eat;
	int	nb;
}	t_philo;

int	check_value(int argc, char **argv, t_philo **value);
int	ft_atoi(char *str);
int	len1(char *str);
int	write_error(char *str);
t_philo	value_copy(t_philo *value);
int	init_mutex(int tot, pthread_mutex_t *mute);

#endif
