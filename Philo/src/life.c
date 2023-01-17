/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakarya <azakarya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:57:26 by azakarya          #+#    #+#             */
/*   Updated: 2023/01/17 23:01:11 by azakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	free_data(t_philos *ptr)
{
	unsigned long	count;

	count = ptr->rules->philo_num;
	pthread_mutex_unlock(ptr->rules->mutex);
	pthread_mutex_destroy(ptr->rules->mutex);
	while (count)
	{
		pthread_mutex_unlock(ptr[count - 1].left_fork);
		if (ptr[count - 1].left_fork && \
		!pthread_mutex_destroy(ptr[count - 1].left_fork))
			ft_free(ptr[count - 1].left_fork);
		count--;
	}
	if (ptr->rules->philo_num == 1)
	{
		pthread_mutex_unlock(ptr[0].right_fork);
		if (ptr[0].right_fork && !pthread_mutex_destroy(ptr[0].right_fork))
			ft_free(ptr[0].right_fork);
	}
	free(ptr->rules->mutex);
	usleep(1000 * 500);
	free(ptr);
	return (1);
}

static void	*ft_deathroutine(void *arg)
{
	t_philos		*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(philo->rules->mutex);
	++philo->rules->loaded;
	pthread_mutex_unlock(philo->rules->mutex);
	while (1)
	{
		if (philo->rules->loaded != philo->rules->philo_num + 1)
			continue ;
		usleep(philo->rules->philo_num * 15);
		if (check_death(philo))
			return (NULL);
	}
	return (NULL);
}

static void	*ft_mainroutine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(philo->rules->mutex);
	++philo->rules->loaded;
	pthread_mutex_unlock(philo->rules->mutex);
	while (philo->rules->loaded != philo->rules->philo_num + 1)
		usleep(10);
	philo->rules->basetime = _timer();
	philo->deathtime = philo->rules->basetime;
	philo->actiontime = philo->rules->basetime;
	pthread_mutex_lock(philo->rules->mutex);
	put_msg(philo);
	pthread_mutex_unlock(philo->rules->mutex);
	while (philo->eatcount != philo->rules->musteat && !philo->rules->death)
	{
		usleep(50);
		if (philo->state == PS_THINKING)
			thinking(philo);
		else if (philo->state == PS_EATING)
			eat(philo);
		else if (philo->state == PS_SLEEPING)
			sleeping(philo);
	}
	return (arg);
}

void	ft_wait(t_philos	*philos)
{
	unsigned long	yeet;

	while (!philos->rules->death)
	{
		yeet = 0;
		while (yeet < philos->rules->philo_num)
		{
			if (philos[yeet].eatcount != philos->rules->musteat)
				break ;
			yeet++;
			if (yeet == philos->rules->philo_num)
				return ;
		}
	}
}

char	init_philos(unsigned long c, t_philos *philos, t_main *rules)
{
	pthread_t		threads;

	if (!philos)
		return (1);
	pthread_mutex_init(rules->mutex, NULL);
	while (++c && c <= rules->philo_num)
	{
		philos[c - 1].state = PS_THINKING;
		if ((c % 2) == 1)
			philos[c - 1].state = PS_SLEEPING;
		if (rules->philo_num == 1)
			pthread_mutex_lock(philos[c - 1].right_fork);
		if (pthread_create(&threads, NULL,
				&ft_mainroutine, (void *)&philos[c - 1]))
			return (free_data(philos));
		pthread_detach(threads);
	}
	if (pthread_create(&threads, NULL,
			&ft_deathroutine, (void *)&philos[0]))
		return (free_data(philos));
	pthread_detach(threads);
	ft_wait(philos);
	free_data(philos);
	return (0);
}
