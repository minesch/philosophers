/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 01:16:40 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/16 01:36:43 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_index % 2 == 0)
		_timer(philo->eat_time);
	while (1)
	{
		pthread_mutex_lock(philo->mutex_l_fork);
		ft_print_message(philo, "has taken left fork");
		pthread_mutex_lock(philo->mutex_r_fork);
		ft_print_message(philo, "has taken right fork");
		pthread_mutex_lock(&philo->monitoring_mutex);
		philo->eat_count++;
		philo->current_time = cur_time();
		pthread_mutex_unlock(&philo->monitoring_mutex);
		ft_print_message(philo, "is eating");
		_timer(philo->eat_time);
		pthread_mutex_unlock(philo->mutex_l_fork);
		pthread_mutex_unlock(philo->mutex_r_fork);
		ft_print_message(philo, "is sleeping");
		_timer (philo->sleep_time);
		ft_print_message(philo, "is thinking");
	}
	return (NULL);
}

int	create_philo(t_main *rules)
{
	int	i;

	i = -1;
	while (++i < rules->philo_nbr)
	{
		pthread_create(&rules->philo[i].philo_thread, NULL,
			routine, (void *)&rules->philo[i]);
	}
	ft_monitoring(rules);
	return (0);
}
