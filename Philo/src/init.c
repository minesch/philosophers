/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 01:16:14 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/16 01:35:58 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args( int argc, char **argv, t_main *rules)
{
	rules->philo = NULL;
	rules->print_mutex = NULL;
	rules->philo_nbr = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eat_time = ft_atoi(argv[3]);
	rules->sleep_time = ft_atoi(argv[4]);
	rules->must_eat_nbr = 0;
	if (rules->philo_nbr <= 0 || rules->death_time <= 0
		|| rules->eat_time <= 0 || rules->sleep_time <= 0)
	{
		printf("Error: provided rules is inadequate!\n");
		return (-1);
	}
	if (argc == 6)
	{
		rules->must_eat_nbr = ft_atoi(argv[5]);
		if (rules->must_eat_nbr <= 0)
		{
			printf("Error: provided rules is inadequate!\n");
			return (-1);
		}
	}
	return (0);
}

int	init_mutexes(t_main *rules)
{
	int	i;

	i = 0;
	rules->fork_mutex = malloc(sizeof(pthread_mutex_t) * rules->philo_nbr);
	rules->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!rules->print_mutex)
	{
		printf("Error: failed to allocate memory for print_mutex\n");
		return (-1);
	}
	if (pthread_mutex_init(rules->print_mutex, NULL) != 0)
		printf("Error: failed to initialize print_mutex\n");
	while (i < rules->philo_nbr)
	{
		if (pthread_mutex_init(&rules->fork_mutex[i], NULL) != 0)
			printf("Error: failed to initialize fork_mutexes!\n");
		i++;
	}
	return (0);
}

int	init_philo(t_main *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_nbr)
	{
		rules->philo[i].philo_index = i + 1;
		rules->philo[i].mutex_l_fork = &(rules->fork_mutex[i]);
		if (i != rules->philo_nbr - 1)
			rules->philo[i].mutex_r_fork = &(rules->fork_mutex[i + 1]);
		else
			rules->philo[i].mutex_r_fork = &(rules->fork_mutex[0]);
		rules->philo[i].eat_count = 0;
		rules->philo[i].death_time = rules->death_time;
		rules->philo[i].eat_time = rules->eat_time;
		rules->philo[i].sleep_time = rules->sleep_time;
		rules->philo[i].print_mutex = rules->print_mutex;
		if (pthread_mutex_init(&rules->philo[i].monitoring_mutex, NULL) != 0)
			return (-1);
		rules->philo[i].start_time = cur_time();
		rules->philo[i].current_time = cur_time();
		i++;
	}
	return (0);
}
