/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:53 by lide              #+#    #+#             */
/*   Updated: 2022/08/11 19:35:41 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_wait(int time_to_wait)
{
	long time;
	long new_time;

	time = get_time();
	new_time = get_time();
	while (new_time - time < time_to_wait)
	{
		usleep(100);
		new_time = get_time();
	}
}

void	death_timer(t_philo *value)
{
	struct timeval	time;
	struct timeval	new_time;
	long timer;

	gettimeofday(&time, NULL);
	while (*value->check == 0)
	{
		usleep(10);
		gettimeofday(&new_time, NULL);
		timer = (new_time.tv_sec - time.tv_sec) * 1000;
		timer += (new_time.tv_usec - time.tv_usec) / 1000;
		if (timer >= value->die)/*&& value->check == 0*/
		{
			*value->check = 1;
			gettimeofday(&time, NULL);
			timer = (time.tv_sec * 1000) + (time.tv_usec / 1000) - value->time;
			pthread_mutex_lock(value->wright);
			printf("%ld \033[0;91m%d died\n\033[0m", timer, value->nb + 1);
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

int print_action(t_philo *value, int verif)
{
	long	time;

	if (*value->check == 0)
	{
		pthread_mutex_lock(value->wright);
		time = get_time() - value->time;
		if (verif == 1)
			printf("%ld "FORK, time, value->nb + 1);
		if (verif == 2)
			printf("%ld "EAT, time, value->nb + 1);
		if (verif == 3)
			printf("%ld "SLEEP, time, value->nb + 1);
		if (verif == 4)
			printf("%ld "THINK, time, value->nb + 1);
		pthread_mutex_unlock(value->wright);
	}
	return (0);
}

void	life(t_philo *value)
{
	pthread_t	death[1];
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
		usleep(50);
	while (!(*value->check) && value->nb_eat != 0 && value->tot > 1)
	{
		pthread_mutex_lock(&value->mt[value->nb]);
		pthread_mutex_lock(&value->mt[j]);
		print_action(value, 1);
		print_action(value, 1);
		*value->eat = 1;
		print_action(value, 2);
		ft_wait(value->t_eat);
		pthread_mutex_unlock(&value->mt[value->nb]);
		pthread_mutex_unlock(&value->mt[j]);
		print_action(value, 3);
		ft_wait(value->sleep);
		print_action(value, 4);
		value->nb_eat -= 1;
	}
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

	// while (!(*value->check) && value->nb_eat != 0)
	// {
	// 	// printf("SLEEP = %d\n", value->sleep);
	// 	pthread_mutex_lock(&value->mt[value->nb]);
	// 	pthread_mutex_lock(&value->mt[j]);
	// 	time = get_time() - value->time;
	// 	pthread_mutex_lock(value->wright);
	// 	printf("%ld %d has taken a fork\n", time, value->nb + 1);
	// 	pthread_mutex_unlock(value->wright);
	// 	*value->eat = 1;
	// 	time = get_time() - value->time;
	// 	pthread_mutex_lock(value->wright);
	// 	printf("%ld %d is eating\n", time, value->nb + 1);
	// 	pthread_mutex_unlock(value->wright);
	// 	usleep(value->t_eat);
	// 	pthread_mutex_unlock(&value->mt[value->nb]);
	// 	pthread_mutex_unlock(&value->mt[j]);
	// 	time = get_time() - value->time;
	// 	printf("%ld %d is sleeping\n", time, value->nb + 1);
	// 	usleep(value->sleep);
	// 	time = get_time() - value->time;
	// 	printf("%ld %d is thinking\n", time, value->nb + 1);
	// 	value->nb_eat -= 1;
	// }

		// if (ft_putnbr(time))
		// {
		// 	*value->check = 1;
		// 	pthread_mutex_unlock(value->wright);
		// 	return(write_error("Error: malloc ft_putnbr"));
		// }
		// if (ft_putnbr((long)(value->nb + 1)))
		// {
		// 	*value->check = 1;
		// 	pthread_mutex_unlock(value->wright);
		// 	return(write_error("Error: malloc ft_putnbr\n"));
		// }
		// write(1, str, len1(str));
