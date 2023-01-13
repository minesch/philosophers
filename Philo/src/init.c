/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:45:49 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/13 23:41:10 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	*routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	if (philos->index % 2 == 0)
		usleep(100);
	philos->rules->start_time = cur_time();
	while (1)
		eat(philos);

}

void	create_philos(t_philos *philos)
{
	int	i;

	i = -1;
	philos->rules->thread = malloc(sizeof(pthread_t) * philos->rules->ph_count);
	while (++i <= philos->rules->ph_count - 1)
		pthread_create(&philos[i].rules->thread, NULL, &routine, &philos[i]);
	i = -1;
	while (++i <= philos->rules->ph_count - 1)
		pthread_detach(philos[i].rules->thread);
	check_death(philos);
}

void	init_philos(t_philos *philos)
{
	int				i;

	i = -1;
	philos->rules->fork_mutex = malloc(sizeof(pthread_mutex_t) \
	* philos->rules->ph_count);
	while (++i < philos->rules->ph_count)
		pthread_mutex_init(philos->rules->fork_mutex, NULL);
	i = -1;
	while (++i <= philos->rules->ph_count - 1)
	{
		philos[i].left_fork = &philos->rules->fork_mutex[i];
		if (i == philos->rules->ph_count)
			philos[i].right_fork = &philos->rules->fork_mutex[0];
		else
			philos[i].right_fork = &philos->rules->fork_mutex[i + 1];
	}
	create_philos(philos);
}
