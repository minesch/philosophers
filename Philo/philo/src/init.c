/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:45:49 by azakarya          #+#    #+#             */
/*   Updated: 2022/12/29 00:06:16 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	create_philos(t_philos *philos)
{
	pthread_t	thr;
	int			i;

	i = -1;
	thr = malloc(sizeof(pthread_t) * philos->rules->ph_count);
	while (++i <= philos->rules->ph_count)
	{
		pthread_create(&thr[i], NULL, &routine, &philos[i]);
	}
}

int	init_philos(t_philos *philos)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = -1;
	mutex = malloc(sizeof(pthread_mutex_t) * philos->rules->ph_count);
	pthread_mutex_init(&mutex, NULL);
	while (++i <= philos->rules->ph_count)
	{
		philos[i].left_fork = &mutex[i];
		if (i == philos->rules->ph_count)
			philos[i].right_fork = &mutex[0];
		else
			philos[i].right_fork = &mutex[i + 1];
	}
	if (create_philos(philos) == 1)
		return (1);
	return (0);
}
