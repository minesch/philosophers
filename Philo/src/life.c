/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:59:24 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/14 00:01:03 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	print_action(char *str, t_philos *philos)
{
	pthread_mutex_lock(philos->rules->print_mutex);
	printf("%lu %d %s", cur_time() - philos->rules->start_time,
		philos->index + 1, str);
	pthread_mutex_unlock(philos->rules->print_mutex);
}

void	check_death(t_philos *philos)
{
	int	i;
	int	curtime;

	i = -1;
	while (++i < philos->rules->ph_count)
			philos[i].last_eat_time = cur_time();
	i = -1;
	while (++i < philos->rules->ph_count)
	{
		curtime = cur_time();
		if ((long long int)(curtime - \
		philos[i].last_eat_time) > philos->rules->die)
		{
			pthread_mutex_lock(philos->rules->print_mutex);
			printf("%zu %d %s\n", curtime - philos->rules->start_time, \
				philos[i].index, "died");
			break ;
		}
		if (i == philos->rules->ph_count - 1)
			i = -1;
	}
	i = -1;
	while (++i < philos->rules->ph_count)
		pthread_mutex_destroy(philos->rules->fork_mutex);

}

void	thinking(t_philos *philos)
{
	print_action(" is thinking\n", philos);
	eat(philos);
}

void	sleeping(t_philos *philos)
{
	print_action(" is sleeping\n", philos);
	_timer((int)(philos->rules->sleep));
	thinking(philos);
}

void	eat(t_philos *philos)
{
	pthread_mutex_lock(philos->left_fork);
	print_action(" has taken a fork\n", philos);
	pthread_mutex_lock(philos->right_fork);
	print_action(" has taken a fork\n", philos);
	philos->eat_count += 1;
	_timer((int)(philos->rules->eat));
	philos->last_eat_time = cur_time();
	print_action(" is eating\n", philos);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
	sleeping(philos);
}
