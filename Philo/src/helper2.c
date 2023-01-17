/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:57:21 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/17 23:02:00 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_time(t_philos *philo, t_philostates state)
{
	if (state == PS_DEAD)
		return (_timer() - philo->deathtime
			>= philo->rules->die);
	if (state == PS_EATING)
		return (_timer() - philo->actiontime
			>= philo->rules->eat);
	if (state == PS_SLEEPING)
		return (_timer() - philo->actiontime
			>= philo->rules->sleep);
	return (0);
}

void	eat(t_philos *philo)
{
	if (ft_time(philo, philo->state))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		++philo->eatcount;
		philo->actiontime = _timer();
		philo->deathtime = _timer();
		philo->state = PS_SLEEPING;
		pthread_mutex_lock(philo->rules->mutex);
		put_msg(philo);
		pthread_mutex_unlock(philo->rules->mutex);
	}
}

void	sleeping(t_philos *philo)
{
	if (ft_time(philo, philo->state))
	{
		philo->state = PS_THINKING;
		pthread_mutex_lock(philo->rules->mutex);
		put_msg(philo);
		pthread_mutex_unlock(philo->rules->mutex);
	}
}

void	thinking(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->state = PS_FORK;
	pthread_mutex_lock(philo->rules->mutex);
	put_msg(philo);
	pthread_mutex_unlock(philo->rules->mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->rules->mutex);
	put_msg(philo);
	pthread_mutex_unlock(philo->rules->mutex);
	philo->state = PS_EATING;
	philo->actiontime = _timer();
	pthread_mutex_lock(philo->rules->mutex);
	put_msg(philo);
	pthread_mutex_unlock(philo->rules->mutex);
}

void	put_msg(t_philos *philo)
{
	if (philo->rules->death)
		return ;
	if (philo->state == PS_DEAD)
		printf("[%lu] [%lu] [%s]\n",
			_timer() - philo->rules->basetime,
			philo->num, "died");
	else if (philo->state == PS_EATING)
		printf("[%lu] [%lu] [%s]\n",
			_timer() - philo->rules->basetime,
			philo->num, "is eating");
	else if (philo->state == PS_SLEEPING)
		printf("[%lu] [%lu] [%s]\n",
			_timer() - philo->rules->basetime,
			philo->num, "is sleeping");
	else if (philo->state == PS_THINKING)
		printf("[%lu] [%lu] [%s]\n",
			_timer() - philo->rules->basetime,
			philo->num, "is thinking");
	else if (philo->state == PS_FORK)
		printf("[%lu] [%lu] [%s]\n",
			_timer() - philo->rules->basetime,
			philo->num, "has taken a fork");
}
