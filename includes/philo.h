/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:29:30 by lide              #+#    #+#             */
/*   Updated: 2022/08/09 18:41:55 by lide             ###   ########.fr       */
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
	int				tot;
	int				die;
	int				eat;
	int				sleep;
	int				nb_eat;
	int				nb;
	int				*check;
	pthread_mutex_t	*mt;
	pthread_mutex_t	*wright;
}	t_philo;

int			check_value(int argc, char **argv, t_philo *value);
int			ft_atoi(char *str);
int			len1(char *str);
int			write_error(char *str);
t_philo		*value_copy(t_philo *value, int i);
int			init_mutex(int tot, t_philo *value);
pthread_t	*init_philo(int tot);
int			free_create(int verif ,char *str, pthread_t *philo, t_philo *value);

#endif
