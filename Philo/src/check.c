/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 01:16:33 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/16 01:41:59 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("[%llu] [%d] [%s]\n", cur_time() - philo->start_time,
		philo->philo_index, str);
	pthread_mutex_unlock(philo->print_mutex);
}

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitoring_mutex);
	if (cur_time() - philo->current_time > philo->death_time)
		return (1);
	pthread_mutex_unlock(&philo->monitoring_mutex);
	return (0);
}

int	thread_cycle_limit(t_main *rules)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (death_check(&rules->philo[i]) == 0 && i < rules->philo_nbr)
	{
		if (rules->philo[i].eat_count >= rules->must_eat_nbr)
			j++;
		if (j == rules->philo_nbr)
			return (1);
		i++;
	}
	return (0);
}

void	ft_monitoring(t_main *rules)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == rules->philo_nbr)
		i = 0;
		if (death_check(&rules->philo[i]) == 1)
		{
			pthread_mutex_lock(rules->print_mutex);
			pthread_mutex_unlock(&rules->philo[i].monitoring_mutex);
			printf("[%llu] [%d] [%s]\n", cur_time() - \
			rules->philo->current_time, rules->philo[i].philo_index, "died");
			break ;
		}
		else if (rules->must_eat_nbr != 0)
		{
			if (thread_cycle_limit(rules) == 1)
				break ;
		}
		i++;
	}
}
