/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:28:53 by lide              #+#    #+#             */
/*   Updated: 2022/08/09 18:55:34 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	life(t_philo *value)
{
	pthread_mutex_lock(value->wright);
	printf("debut\n");
	printf("tot %d\n", value->tot);
	printf("die %d\n", value->die);
	printf("eat %d\n", value->eat);
	printf("sleep %d\n", value->sleep);
	printf("nb_eat %d\n", value->nb_eat);
	printf("nb %d\n", value->nb);
	printf("check %d\n", *value->check);
	printf("fin\n\n");
	pthread_mutex_unlock(value->wright);
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
		new = value_copy(value, i);//en cas de crache renvoyer dans une fonction qui fera un join
		if (pthread_create(&philo[i], NULL, (void *)&life, (void *)new))
			return (free_create(1, "Error: pthread_create\n", philo, value));
	}
	i = -1;
	while (++i < value->tot)
		if (pthread_join(philo[i], NULL))
			return (free_create(1, "Error: pthread_join\n", philo, value));
	free(philo);
	free(value->mt);//doit utiliser destroy
	free(value->wright);
	return (0);
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
