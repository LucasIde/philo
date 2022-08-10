/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:53 by lide              #+#    #+#             */
/*   Updated: 2022/08/10 19:30:09 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	death_timer(t_philo *value)
{
	struct timeval	time;
	struct timeval	new_time;
	long timer;

	gettimeofday(&time, NULL);
	while (*value->check == 0)
	{
		gettimeofday(&new_time, NULL);
		timer = (new_time.tv_sec - time.tv_sec) * 1000;
		timer += (new_time.tv_usec - time.tv_usec) / 1000;
		if (timer >= value->die)
		{
			*value->check = 1;
			gettimeofday(&time, NULL);
			timer = (time.tv_sec * 1000) + (time.tv_usec / 1000);
			pthread_mutex_lock(value->wright);
			printf("%ld %d died\n", timer, value->nb);
			pthread_mutex_unlock(value->wright);
		}
		if (*value->eat == 1 && *value->check == 0)
		{
			gettimeofday(&time, NULL);
			*value->eat = 0;
		}
	}
}

long	get_time(void)
{
	struct timeval	time;
	long	t;

	gettimeofday(&time, NULL);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (t);
}

void	life(t_philo *value)
{
	pthread_t	death[1];
	long		time;
	int			eat;
	int			j;

	eat = 0;
	value->eat = &eat;
	if (*value->check == 0)
		if (pthread_create(&death[0], NULL, (void *)death_timer, (void *)value))
			*value->check = 1;
	if (value->nb == 0)
		j = value->tot - 1;
	else
		j = value->nb - 1;
	if (value->nb % 2 != 0)
		usleep(3);
	while (!(*value->check) && value->nb_eat != 0)
	{
		pthread_mutex_lock(&value->mt[value->nb]);
		pthread_mutex_lock(&value->mt[j]);
		time = get_time();
		pthread_mutex_lock(value->wright);
		printf("%ld %d has taken a fork\n", time, value->nb);
		pthread_mutex_unlock(value->wright);
		time = get_time();
		*value->eat = 1;
		pthread_mutex_lock(value->wright);
		printf("%ld %d is eating\n", time, value->nb);
		pthread_mutex_unlock(value->wright);
		usleep(value->t_eat);
		pthread_mutex_unlock(&value->mt[value->nb]);
		pthread_mutex_unlock(&value->mt[j]);
		time = get_time();
		printf("%ld %d is sleeping\n", time, value->nb);
		usleep(value->sleep);
		time = get_time();
		printf("%ld %d is thinking\n", time, value->nb);
		value->nb_eat -= 1;
	}
	// pthread_mutex_lock(value->wright);
	// printf("debut\n");
	// printf("tot %d\n", value->tot);
	// printf("die %d\n", value->die);
	// printf("eat %d\n", value->t_eat);
	// printf("sleep %d\n", value->sleep);
	// printf("nb_eat %d\n", value->nb_eat);
	// printf("nb %d\n", value->nb);
	// printf("check %d\n", *value->check);
	// printf("fin\n\n");
	// pthread_mutex_unlock(value->wright);
	pthread_join(death[0], NULL);
	free(value);//doit destoy le mutex a la mort et free check
}

int	create_philo(t_philo *value)
{
	pthread_t	*philo;
	int	i;
	t_philo	*new;

	if (init_mutex(value->tot, value))
		return (write_error("Error: malloc mutex\n"));
	philo = init_philo(value->tot);
	if (!philo)
		return (free_create(0, "Error: malloc philo\n", philo, value));
	i = -1;
	while (++i < value->tot)
	{
		new = value_copy(value, i);//en cas de crash renvoyer dans une fonction qui fera un join
		if (!new)
			return (error_value(value, i, philo));
		if (pthread_create(&philo[i], NULL, (void *)&life, (void *)new))
			return (free_create(1, "Error: pthread_create\n", philo, value));
	}
	i = -1;
	while (++i < value->tot)
		if (pthread_join(philo[i], NULL))
			return (free_create(1, "Error: pthread_join\n", philo, value));
	return (free_create(2, NULL, philo, value));
}


int	main(int argc, char **argv)//doit free une seule fois value check
{
	t_philo	value;

	if (argc < 5)
		return (write_error("not enough arguments\n"));
	else if (argc > 6)
		return (write_error("too much arguments\n"));
	if (check_value(argc, argv, &value))
		return (1);
	if (create_philo(&value))
		return (write_error("error: creation of pthread\n"));
	return (0);
}
