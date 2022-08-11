/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:29:30 by lide              #+#    #+#             */
/*   Updated: 2022/08/11 19:30:04 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>

# define FORK "\033[0;92m%d has taken a fork\033[0m\n"
# define EAT "\033[0;96m%d is eating\033[0m\n"
# define SLEEP "\033[1;95m%d is sleeping\033[0m\n"
# define THINK "\033[0;93m%d is thinking\033[0m\n"

typedef struct s_philo
{
	int				tot;
	int				die;
	int				t_eat;
	int				sleep;
	int				nb_eat;
	int				nb;
	long			time;
	int				*eat;
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
int			error_value(t_philo *value, int i, pthread_t *philo);
long		get_time(void);
int			ft_putnbr(long n);

#endif
