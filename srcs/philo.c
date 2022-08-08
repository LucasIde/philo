/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:53 by lide              #+#    #+#             */
/*   Updated: 2022/08/08 11:55:15 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	life(t_philo value);

int	create_philo(t_philo *value)
{
	pthread_t	philo[value->tot];//malloc philo
	pthread_mutex_t	mute[value->tot];
	int	i;
	t_philo	new;

	init_mutex(value->tot, mute);
	i = -1;
	while (++i < value->tot)
	{
		new = value_copy(value);
		if (pthread_create(&philo[i], NULL, (void *)&life, (void *)&i))
			return (1);
	}
	i = -1;
	while (++i < value->tot)
	{
		if ((i % 2) == 0)
			if (pthread_detach(philo[i]))
				return (1);
	}
	i = -1;
	while (++i < value->tot)
	{
		if ((i % 2) != 0)
		{
			if (usleep(10) == -1)
				return (1);
			if (pthread_detach(philo[i]))
				return (1);
		}
	}
}


int	main(int argc, char **argv)
{
	t_philo	value;

	if (argc < 4)
		return (write_error("not enough arguments"));
	else if (argc > 5)
		return (write_error("too much arguments"));
	if (check_value(argc, argv, &value))
		return (1);
	if (create_philo(&value))
		return (write_error("error: creation of pthread"));
	return (0);
}
