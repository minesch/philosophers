/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:59:24 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/15 00:32:06 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

void	print_action(char *str, t_philos *philos)
{
	pthread_mutex_lock(philos->rules->print_mutex);
	printf("[%llu] [%d] [%s]\n", cur_time() - philos->rules->start_time,
		philos->index + 1, str);
	pthread_mutex_unlock(philos->rules->print_mutex);
}

void	check_death(t_philos *philos)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < philos->rules->ph_count)
		{
			if (philos[i].last_eat_time != -1 && (cur_time() - \
					philos[i].last_eat_time) >= philos->rules->die)
			{
				pthread_mutex_lock(philos->rules->print_mutex);
				printf("[%lld] [%d] [%s]\n", (cur_time() - \
				philos[i].last_eat_time), philos[i].index + 1, "died");
				pthread_mutex_unlock(philos->rules->print_mutex);
				return ;
			}
		}
	}
}

void	thinking(t_philos *philos)
{
	print_action("is thinking", philos);
	eat(philos);
}

void	sleeping(t_philos *philos)
{
	print_action("is sleeping", philos);
	_timer((int)(philos->rules->sleep));
	thinking(philos);
}

void	eat(t_philos *philos)
{
	// printf("%lld\n", philos->last_eat_time);
	pthread_mutex_lock(philos->left_fork);
	print_action("has taken a left fork", philos);
	pthread_mutex_lock(philos->right_fork);
	print_action("has taken a right fork", philos);
	print_action("is eating", philos);
	_timer((int)(philos->rules->eat));
	philos->eat_count += 1;
	philos->last_eat_time = cur_time();
	// philos->rules->start_time = philos->last_eat_time;
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
	sleeping(philos);
}
